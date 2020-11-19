//
// Created by Алексей on 18.11.2020.
//

#ifndef OPERATION_DIVISION_H
#define OPERATION_DIVISION_H

#include "../Calculator_src/Operation.h"

class Division : public Operation {
public:
    Division() : Operation("/" , Priority::MIDDLE, 2){};

    ERRORS calc(std::vector<double> &args, double &answer) const override;
};

extern "C"
__declspec(dllexport) Operation* GetOperation(){
    return new Division();
}

#endif //OPERATION_DIVISION_H
