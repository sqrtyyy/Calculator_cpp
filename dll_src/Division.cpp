//
// Created by Алексей on 18.11.2020.
//

#include "Division.h"

Operation::ERRORS Division::calc(std::vector<double> &args, double &answer) const {
    if(args.size() != numOfArgs_) return ERRORS::WRONG_NUMBER_OF_ARGS;
    if(args[0] == 0) return ERRORS::WRONG_DATA_FORMAT;
    answer = args[1] / args[0];
    return ERRORS::OK;
}
