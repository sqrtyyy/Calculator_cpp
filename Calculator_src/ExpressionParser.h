//
// Created by Алексей on 23.11.2020.
//

#ifndef CALCULATOR_EXPRESSIONPARSER_H
#define CALCULATOR_EXPRESSIONPARSER_H

#include <utility>
#include <string>
#include <queue>
#include <list>
#include <any>
#include "Operation.h"

using std::string;
using std::queue;
using std::pair;

class ExpressionParser {
public:
    enum TypeOfToken{
        NUMBER,
        OPERATION,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        UNDEFINED,
    };
    static queue<pair<TypeOfToken, std::any>> parseExpression(string& expression,
                                                              const std::list<Operation*>& possibleOperations);
};


#endif //CALCULATOR_EXPRESSIONPARSER_H
