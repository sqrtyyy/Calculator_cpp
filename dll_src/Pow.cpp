//
// Created by Алексей on 18.11.2020.
//

#include "Pow.h"
#include <cmath>

Operation::ERRORS Pow::calc(std::vector<double> &args, double &answer) const {
    if(args.size() != numOfArgs_) return ERRORS::WRONG_NUMBER_OF_ARGS;
    answer = pow(args[1], args[0]);
    return answer != answer ? ERRORS::WRONG_DATA_FORMAT : ERRORS::OK;
}
