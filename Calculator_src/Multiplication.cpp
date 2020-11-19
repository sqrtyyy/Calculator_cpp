//
// Created by Алексей on 18.11.2020.
//

#include "Multiplication.h"

Operation::ERRORS Multiplication::calc(std::vector<double> &args, double &answer) const {
    if(args.size() != numOfArgs_) return ERRORS::WRONG_NUMBER_OF_ARGS;
    answer = args[0] * args[1];
    return answer != answer ? WRONG_DATA_FORMAT : OK;
}
