#pragma once

#include <exception>
#include "../common/gpioerror.h"

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


