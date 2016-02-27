#include <wiringPi.h>
#include <softPwm.h>
#include "motor.h"

namespace {
    bool finished_setup_gpio;
    constexpr int PWM_RANGE = 256;
}

bool MotorClass::init(int pin1_number, int pin2_number, bool direction)
{
    this->in1pin = pin1_number;
    this->in2pin = pin2_number;
    this->direction = direction;
    if (!finished_setup_gpio) {
        if (wiringPiSetupGpio() == -1) {
            return false;
        }
        finished_setup_gpio = true;
    }
    softPwmCreate(pin1_number, 0, PWM_RANGE); 
    softPwmCreate(pin2_number, 0, PWM_RANGE);
    this->mode = MotorMode::Stop;
    this->duty = 0;
    return true;
}

MotorClass::~MotorClass(void)
{
    this->setMotor(MotorMode::Stop, 0);
}

bool MotorClass::setMotor(MotorMode mode, double duty)
{
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
        softPwmWrite(this->in1pin, 0);
        softPwmWrite(this->in2pin, 0);
        break;
    case MotorMode::Brake:
        softPwmWrite(this->in1pin, 1);
        softPwmWrite(this->in2pin, 1);
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

const char* SetupGpioException::what() const noexcept
{
    return "failed in SetupGpio";
}

