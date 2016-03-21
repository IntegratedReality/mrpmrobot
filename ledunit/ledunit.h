#pragma once

#include <exception>
#include "../gpioerror.h"

class LedUnit
{
    bool state;
    int inpin;
public:
    LedUnit(int pinNumber);
    ~LedUnit(void);
    void on();
    void off();
    int getstate() {return state;};
};


