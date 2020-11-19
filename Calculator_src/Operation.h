//
// Created by aleksei on 29.10.2020.
//

#ifndef CALCULATOR_OPERATION_H
#define CALCULATOR_OPERATION_H
#include <string>
#include <utility>
#include <vector>

class Operation {
protected:
    enum Priority{
        VERY_LOW = 0,
        LOW,
        MIDDLE,
        HIGH
    };
    Operation(std::string  name,Priority priority, unsigned short numOfArgs)
            : priority_(priority),name_(std::move(name)), numOfArgs_(numOfArgs){};
public:
    enum ERRORS{
        OK = 0,
        WRONG_NUMBER_OF_ARGS,
        WRONG_DATA_FORMAT
    };
    virtual ERRORS calc(std::vector<double>& args, double& answer) const = 0;
    bool isThisOperation(const std::string& operation) const;
    unsigned short getNumOfArgs() const;
    Priority getPriority() const;
    static std::string getErrMsg(ERRORS errors);
    virtual ~Operation() = default;
protected:
    Priority priority_;
    const std::string name_;
    unsigned short numOfArgs_;

};


#endif //CALCULATOR_OPERATION_H
