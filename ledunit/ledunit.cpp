#include <iostream>
#include <wiringPi.h>
#include "ledunit.h"

namespace {
    bool finished_setup_gpio;
}


LedUnit::LedUnit(int pinNumber) : inpin(pinNumber), state(false)
{
    if (!finished_setup_gpio) {
        if (wiringPiSetupGpio() == -1) {
            throw SetupGpioException();    
         }
        finished_setup_gpio = true;
    }
    pinMode(pinNumber, OUTPUT); 
}

LedUnit::~LedUnit(void)
{
    LedUnit::off();
}

void LedUnit::on()
{
    digitalWrite(inpin, 1);
    state = true;
}

void LedUnit::off()
{
    digitalWrite(inpin, 0);
    state = false;
}

