//
// Created by aleksei on 29.10.2020.
//

#include "Addition.h"

Operation::ERRORS Addition::calc(std::vector<double> &args, double &answer) const {
    if(args.size() != numOfArgs_) return ERRORS::WRONG_NUMBER_OF_ARGS;
    answer = args[0] + args[1];
    return ERRORS::OK;
}
