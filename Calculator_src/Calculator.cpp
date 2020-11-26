//
// Created by aleksei on 29.10.2020.
//

#include <iostream>
#include "Calculator.h"

double Calculator::calculate(string expression){
    if(error == DLL_IMPORT_ERROR) return NAN;
    error = Errors::OK;
    auto tokensValueType = ExpressionParser::parseExpression(expression, possibleOperations);
    CalculateExpression(tokensValueType);
    double result = getResult();
    clearStacks();
    return result;
}

Calculator::Calculator(){
    LoadDlls();
}

void Calculator::LoadDlls() {
    WIN32_FIND_DATA FindData;
    HANDLE Handle = FindFirstFile(path, &FindData);
    FindNextFile(Handle, &FindData);
    while( FindNextFile(Handle, &FindData) )
    {
        char pathToDll[MAX_PATH] = "Plugins\\";
        strcat(pathToDll, FindData.cFileName);
        HMODULE hDLL = LoadLibrary(pathToDll);
        GetModuleFileName(hDLL, pathToDll, MAX_PATH);
        if(hDLL != nullptr){
            Dlls.push_back(hDLL);
            FARPROC fun =  GetProcAddress(hDLL,"GetOperation" );
            possibleOperations.push_back(reinterpret_cast<Operation*>(fun()));
        } else {
            error = Errors::DLL_IMPORT_ERROR;
            break;
        }
    }
}

void Calculator::pushOperationInStack(Operation* operation) {
    while(!error && !operations.empty() && operations.top() != nullptr &&
    operations.top()->getPriority() > operation->getPriority()){
        CalculateLastOperation();
    }
    if(!error) operations.push(operation);
}

std::vector<double> Calculator::generateArgsArray(unsigned int argNum) {
    std::vector<double> args(argNum);
    int i;
    for(i = 0; i < argNum && !numbers.empty(); i++){
        args[i] = numbers.top();
        numbers.pop();
    }
    if(numbers.empty() && i != argNum){
        error = Errors::NOT_ENOUGH_NUMBERS;
    }
    return args;
}

void Calculator::CalculateLastOperation() {
    Operation* curOperation = operations.top();
    double  answer;
    auto args = generateArgsArray(curOperation->getNumOfArgs());
    if(error) return;
    auto errOp = curOperation->calc(args, answer);
    if(errOp){
        error = ERROR_IN_FUN;
        std::cout << Operation::getErrMsg(errOp);
    } else {
        numbers.push(answer);
        operations.pop();
    }
}

void Calculator::clearStacks() {
    while (!numbers.empty()){
        numbers.pop();
    }
    while (!operations.empty()){
        operations.pop();
    }
}

Calculator::~Calculator() {
    for (Operation* op : possibleOperations){
        delete op;
    }
    for(auto hDll : Dlls){
        FreeLibrary(hDll);
    }

}

void Calculator::goToPrevBracket() {
    while (!error && !operations.empty() && operations.top() != nullptr){
        CalculateLastOperation();
    }
    if(!error){
        if(!operations.empty() && operations.top() == nullptr) {
            operations.pop();
        } else {
            error = WRONG_BRACKETS;
        }
    }
}

Calculator::Errors Calculator::getError() const {
    return error;
}

string Calculator::GetErrMsg(Errors error) {
    string msg;
    switch (error) {
        case WRONG_BRACKETS:
            msg = "Wrong sequence of brackets";
            break;
        case WRONG_FUN:
            msg = "Function does not exists";
            break;
        case ERROR_IN_FUN:
            msg = "Error in fun occurred";
            break;
        case DLL_IMPORT_ERROR:
            msg = "One of dlls wasn't loaded";
            break;
        case NOT_ENOUGH_FUNCTIONS:
            msg = "Wrong sequence of functions";
            break;
        case NOT_ENOUGH_NUMBERS:
            msg = "Wrong sequence of numbers";
            break;
        default:
            msg = "OK";
    }
    return msg;
}

void Calculator::CalculateExpression(queue<pair<ExpressionParser::TypeOfToken, std::any>>& tokensValueType) {
    while (!error && !tokensValueType.empty()){
        auto type = tokensValueType.front().first;
        auto value = tokensValueType.front().second;
        switch (type) {
            case ExpressionParser::LEFT_BRACKET:
                operations.push(nullptr);
                break;
            case ExpressionParser::RIGHT_BRACKET:
                goToPrevBracket();
                break;
            case ExpressionParser::NUMBER:
                numbers.push(std::any_cast<double>(value));
                break;
            case ExpressionParser::OPERATION:
                pushOperationInStack(std::any_cast<Operation*>(value));
                break;
            case ExpressionParser::UNDEFINED:
                error = Errors::WRONG_FUN;
        }
        tokensValueType.pop();
    }
    while(!error && !operations.empty()){
        CalculateLastOperation();
    }
}

double Calculator::getResult() {
    if(error) return NAN;
    if(numbers.empty()){
        error = Errors::NOT_ENOUGH_NUMBERS;
        return NAN;
    }
    double result = numbers.top();
    numbers.pop();
    if(!numbers.empty()){
        error = Errors::NOT_ENOUGH_NUMBERS;
        result = NAN;
    }
    return result;
}
