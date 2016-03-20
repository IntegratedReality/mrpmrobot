#pragma once

#include <exception>

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


class SetupGpioException : public std::exception
{
public:
    const char* what() const noexcept override; 
};
