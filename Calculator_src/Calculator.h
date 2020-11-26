//
// Created by aleksei on 29.10.2020.
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include <string>
#include <stack>
#include <list>
#include <windows.h>

#include "Addition.h"
#include "Multiplication.h"
#include "ExpressionParser.h"

using std::stack;

class Calculator {
public:
    enum Errors{
        OK,
        DLL_IMPORT_ERROR,
        NOT_ENOUGH_NUMBERS,
        NOT_ENOUGH_FUNCTIONS,
        WRONG_BRACKETS,
        WRONG_FUN,
        ERROR_IN_FUN,
    };

    double calculate(std::string expression);

    Errors getError() const;


    Calculator();

    ~Calculator();

    static std::string GetErrMsg(Errors error);

private:
    stack<Operation*> operations;
    stack<double> numbers;
    std::list<Operation*> possibleOperations = {new Addition(), new Multiplication()};

    char path[MAX_PATH] = "Plugins\\*.*";
    std::list<HMODULE> Dlls;
    Errors error = OK;

    void clearStacks();
    void LoadDlls();
    void pushOperationInStack(Operation* operation);
    void calcReminder();
    std::vector<double> generateArsArray(unsigned int argNum);
    void CalculateLastOperation();
    void goToPrevBracket();

};


#endif //CALCULATOR_CALCULATOR_H
