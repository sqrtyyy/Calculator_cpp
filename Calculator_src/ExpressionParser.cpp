//
// Created by Алексей on 23.11.2020.
//

#include "ExpressionParser.h"
#include <exception>

using std::make_pair;


static string SeparateToken(string &expression, string& delimiter){
    int pos = expression.find(delimiter);
    if (pos == string::npos){
        pos = expression.length();
    }
    string curToken = expression.substr(0, pos);
    if (pos != expression.length()){
        expression.erase(0, delimiter.length());
    }
    expression.erase(0, pos);
    return curToken;
}


queue<pair<ExpressionParser::TypeOfToken, std::any>> ExpressionParser::parseExpression(string &expression,
                                                                                       const std::list<Operation*>& possibleOperations){
    if(possibleOperations.empty()) return {};
    string delimiter = " ";
    queue<pair<ExpressionParser::TypeOfToken, std::any>> tokensValAndType;
    bool isUndefined = false;
    while (!isUndefined && !expression.empty()){
        TypeOfToken typeOfToken = UNDEFINED;
        std::any value;
        auto curToken = SeparateToken(expression, delimiter);

        if (curToken.empty()) continue;
        if (curToken == "("){
            typeOfToken = LEFT_BRACKET;
            value = nullptr;

        } else if (curToken == ")"){
            typeOfToken = RIGHT_BRACKET;
            value = nullptr;
        } else {
            try {
                value = std::stod(curToken);
                typeOfToken = NUMBER;
            } catch (std::exception& exception) {
                typeOfToken = OPERATION;
                for (auto curOperation : possibleOperations) {
                    if (curOperation->isThisOperation(curToken)) {
                        value = curOperation;
                        break;
                    }
                }
                isUndefined = !value.has_value();
            }
        }
        tokensValAndType.push(make_pair(typeOfToken, value));
    }
    if(isUndefined){
        tokensValAndType = {};
        tokensValAndType.push(make_pair(UNDEFINED, nullptr));
    }
    return tokensValAndType;
}
