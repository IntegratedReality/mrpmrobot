#pragma once

#include <exception>

enum class MotorMode
{
    Forward,
    Back,
    Stop,
    Brake
};

class MotorClass
{
    int in1pin;
    int in2pin;
    MotorMode mode;
    void stop_wait_100us(void);
    bool direction;
public:
    bool init(int in1pin, int in2pin, bool direction);
    ~MotorClass(void);
    bool setMotor(MotorMode mode);
    MotorMode getMotorMode() const;
};

class SetupGpioException : public std::exception
{
public:
    const char* what() const noexcept override; 
};
