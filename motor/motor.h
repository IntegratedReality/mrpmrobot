#pragma once

#include <exception>
#include "../common/gpioerror.h"

enum class MotorMode
{
    Move,
    Stop,
    Brake
};

class MotorClass
{
    int in1pin;
    int in2pin;
    MotorMode mode;
    bool direction;
    double duty;
public:
    MotorClass(int in1pin, int in2pin, bool direction);
    ~MotorClass(void);
    bool setMotor(MotorMode mode, double duty);
    MotorMode getMotorMode() const;
    double getMotorDuty() const;
};

