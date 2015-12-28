#include <wiringPi.h>
#include "motor.h"

namespace {
    bool finished_setup_gpio;
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
    pinMode(pin1_number, OUTPUT);
    pinMode(pin2_number, OUTPUT);
    this->mode = MotorMode::Stop;
    return true;
}

MotorClass::~MotorClass(void)
{
    this->setMotor(MotorMode::Stop);
}

bool MotorClass::setMotor(MotorMode mode)
{
    if (this->mode == MotorMode::Forward) {
        if (mode == MotorMode::Back || mode == MotorMode::Brake) {
            this->stop_wait_100us();
        }
    } else if (this->mode == MotorMode::Back) {
        if (mode == MotorMode::Forward || mode == MotorMode::Brake) {
            this->stop_wait_100us();
        }
    } else if (this->mode == MotorMode::Brake) {
        if (mode == MotorMode::Forward || mode == MotorMode::Back) {
            this->stop_wait_100us();
        }
    }
    this->mode = mode;
    switch (mode) {
    case MotorMode::Forward:
        if (direction) {
            digitalWrite(this->in1pin, 1);
            digitalWrite(this->in2pin, 0);
        } else {
            digitalWrite(this->in1pin, 0);
            digitalWrite(this->in2pin, 1);
        }
        break;
    case MotorMode::Back:
        if (direction) {
            digitalWrite(this->in1pin, 0);
            digitalWrite(this->in2pin, 1);
        } else {
            digitalWrite(this->in1pin, 1);
            digitalWrite(this->in2pin, 0);
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

MotorMode MotorClass::getMotorMode(void) const
{
    return this->mode;
}

const char* SetupGpioException::what() const noexcept
{
    return "failed in SetupGpio";
}

void MotorClass::stop_wait_100us(void)
{
    digitalWrite(this->in1pin, 0);
    digitalWrite(this->in2pin, 0);
    delayMicroseconds(100);
}
