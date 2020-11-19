#ifndef OPERATION_SUBTRACTION_H
#define OPERATION_SUBTRACTION_H

#ifdef MAKEDLL
#  define EXPORT __declspec(dllexport)
#else
#  define EXPORT __declspec(dllimport)
#endif

#include "../Calculator_src/Operation.h"

class Subtraction: public Operation {
public:
    Subtraction() : Operation("-", Operation::LOW, 2) {};

    ERRORS calc(std::vector<double>& args, double& answer) const override;
};

extern "C"
    __declspec(dllexport) Operation* GetOperation(){
        return new Subtraction();;
    }



#endif //OPERATION_SUBTRACTION_H
