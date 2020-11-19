//
// Created by Алексей on 18.11.2020.
//

#ifndef OPERATION_POW_H
#define OPERATION_POW_H

#include "../Calculator_src/Operation.h"

class Pow: public Operation {
public:
    Pow() : Operation("^", Operation::HIGH, 2) {};

    ERRORS calc(std::vector<double>& args, double& answer) const override;
};

extern "C"
__declspec(dllexport) Operation* GetOperation(){
    return new Pow();
}



#endif //OPERATION_POW_H
