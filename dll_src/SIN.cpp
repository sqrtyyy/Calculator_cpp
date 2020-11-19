//
// Created by Алексей on 18.11.2020.
//

#include "SIN.h"
#include <cmath>

Operation::ERRORS SIN::calc(std::vector<double> &args, double &answer) const {
    if(args.size() != numOfArgs_) return ERRORS::WRONG_NUMBER_OF_ARGS;
    answer = sin(args[0]);
    return ERRORS::OK;
}
