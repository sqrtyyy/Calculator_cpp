//
// Created by Алексей on 18.11.2020.
//

#ifndef OPERATION_SIN_H
#define OPERATION_SIN_H


#include "../Calculator_src/Operation.h"

class SIN: public Operation {
public:
    SIN() : Operation("sin", Operation::MIDDLE, 1) {};

    ERRORS calc(std::vector<double>& args, double& answer) const override;
};

extern "C"
__declspec(dllexport) Operation* GetOperation(){
    return new SIN();
}


#endif //OPERATION_SIN_H
