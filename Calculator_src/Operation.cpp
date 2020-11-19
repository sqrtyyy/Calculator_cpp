//
// Created by aleksei on 29.10.2020.
//

#include "Operation.h"

unsigned short Operation::getNumOfArgs() const {
    return numOfArgs_;
}

bool Operation::isThisOperation(const std::string& operation) const {
    return operation == this->name_;
}

Operation::Priority Operation::getPriority() const {
    return priority_;
}

std::string Operation::getErrMsg(ERRORS errors) {
    std::string msg;
    switch (errors) {
        case WRONG_NUMBER_OF_ARGS:
            msg = "Wrong number of arguments";
            break;
        case WRONG_DATA_FORMAT:
            msg = "Wrong data(division by 0 and etc.)";
            break;
        case OK:
            msg = "OK";
    }
    return msg;
}
