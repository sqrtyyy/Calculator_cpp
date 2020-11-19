#include "Subtraction.h"


Operation::ERRORS Subtraction::calc(std::vector<double> &args, double &answer) const {
    if(args.size() != numOfArgs_) return ERRORS::WRONG_NUMBER_OF_ARGS;
    answer = args[1] - args[0];
    return ERRORS::OK;
}



