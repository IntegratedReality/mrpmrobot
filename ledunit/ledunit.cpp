#include <iostream>
#include <wiringPi.h>
#include "ledunit.h"

LedUnit::LedUnit(int pinNumber) : inpin(pinNumber), state(false)
{
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

