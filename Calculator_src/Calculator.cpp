//
// Created by aleksei on 29.10.2020.
//

#include <iostream>
#include <filesystem>
#include "Calculator.h"

using std::string;
namespace fs = std::filesystem;


double Calculator::calculate(std::string expression){
    if(error == DLL_IMPORT_ERROR) return 0;
    error = Errors::OK;
    double result = 0;
    while (!error && !expression.empty()){
        int pos = expression.find(delimiter);
        if(pos == string::npos){
            pos = expression.length();
        }
        string curToken = expression.substr(0, pos);

        if(pos != expression.length()){
            expression.erase(0, delimiter.length());
        }
        expression.erase(0, pos);
        if(curToken.empty()) continue;
        if(curToken == "(") {
            operations.push(nullptr);
            continue;
        }
        if(curToken == ")") {
            goToPrevBracket();
            continue;
        }

        try {
            numbers.push(std::stod(curToken));
        } catch (std::exception& exception) {
            Operation* operation = nullptr;
            for(auto curOperation : possibleOperations){
                if(curOperation->isThisOperation(curToken)){
                    operation = curOperation;
                    break;
                }
            }
            if(operation != nullptr){
                pushOperationInStack(operation);
            } else {
                error = Errors::WRONG_FUN;
            }
        }
    }
    if(error) {
        clearStacks();
        return result;
    }
    calcReminder();
    if(error){
        clearStacks();
        return result;
    }
    result = numbers.top();
    numbers.pop();
    if(!numbers.empty()){
        error = Errors::NOT_ENOUGH_FUNCTIONS;
    }
    clearStacks();
    return result;
}

Calculator::Calculator() {
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

void Calculator::calcReminder() {
    while(!error && !operations.empty()){
        CalculateLastOperation();
    }
}

std::vector<double> Calculator::generateArsArray(unsigned int argNum) {
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
    auto args = generateArsArray(curOperation->getNumOfArgs());
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

Calculator::Errors Calculator::getError() const {
    return error;
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

std::string Calculator::GetErrMsg(Errors error) {
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

