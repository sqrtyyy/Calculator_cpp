//
// Created by aleksei on 29.10.2020.
//

#ifndef CALCULATOR_ADDITION_H
#define CALCULATOR_ADDITION_H

#include "Operation.h"

class Addition : public Operation{
public:
    Addition() : Operation("+", Priority::LOW, 2) {};

    ERRORS calc(std::vector<double>& args, double& answer) const override;

};


#endif //CALCULATOR_ADDITION_H
