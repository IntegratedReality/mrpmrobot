#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include "motor.h"

namespace {
    constexpr int PWM_RANGE = 256;
}

MotorClass::MotorClass(int pin1_number, int pin2_number, bool direction) : in1pin(pin1_number), in2pin(pin2_number), direction(direction)
{
//    if (!finished_setup_gpio) {
//        if (wiringPiSetupGpio() == -1) {
//            throw SetupGpioException();    
//        }
//        finished_setup_gpio = true;
//    }
    softPwmCreate(pin1_number, 0, PWM_RANGE); 
    softPwmCreate(pin2_number, 0, PWM_RANGE);
    this->mode = MotorMode::Stop;
    this->duty = 0;
}

MotorClass::~MotorClass(void)
{
    this->setMotor(MotorMode::Stop, 0);
}

bool MotorClass::setMotor(MotorMode mode, double duty)
{
    //std::cout << duty << std::endl;
    this->mode = mode;
    this->duty = duty;
    if (!this->direction) {
        this->duty = -1 * this->duty;
    }
    switch (mode) {
    case MotorMode::Move:
        if (this->duty >= 0) {
            softPwmWrite(this->in1pin, static_cast<int>(this->duty * 256));
            softPwmWrite(this->in2pin, 0);
        } else {
            softPwmWrite(this->in1pin, 0);
            softPwmWrite(this->in2pin, static_cast<int>(this->duty * -256));
        }
        break;
    case MotorMode::Stop:
        digitalWrite(this->in1pin, 0);
        digitalWrite(this->in2pin, 0);
        break;
    case MotorMode::Brake:
        digitalWrite(this->in1pin, 1);
        digitalWrite(this->in2pin, 1);
        break;
    default:
        return false;
    }
    return true;
}

double MotorClass::getMotorDuty(void) const
{
    if (!direction) {
        return -1 * this->duty;
    } else {
        return this->duty;
    }
}

MotorMode MotorClass::getMotorMode(void) const
{
    return this->mode;
}

