#pragma once

#include <exception>
#include "../common/gpioerror.h"

class LedUnit
{
    int inpin;
    bool state;
public:
    LedUnit(int pinNumber);
    ~LedUnit(void);
    void on();
    void off();
    int getstate() {return state;};
};


