#include <iostream>
#include <string>
#include "Calculator_src/Calculator.h"



using std::cin;

int main() {
    std::string expression;
    Calculator calculator;
    std::getline(cin, expression);
    double result = calculator.calculate(expression);
    if(!calculator.getError()){
        std::cout << result << std::endl;
    } else {
        std::cout << Calculator::GetErrMsg(calculator.getError()) << std::endl;
    }
    system("pause ");
    return 0;
}
