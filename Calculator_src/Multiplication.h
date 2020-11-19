//
// Created by Алексей on 18.11.2020.
//

#ifndef CALCULATOR_MULTIPLICATION_H
#define CALCULATOR_MULTIPLICATION_H
#include "Operation.h"

class Multiplication : public Operation {
public:
    Multiplication() : Operation("*", Priority::MIDDLE, 2) {};

    ERRORS calc(std::vector<double>& args, double& answer) const override;
};


#endif //CALCULATOR_MULTIPLICATION_H
