#include "ledunit.h"
#include <iostream>
#include <wiringPi.h>

int main(void)
{
    LedUnit ledunit(27);
    
    ledunit.on();
    std::cout << ledunit.getstate() << std::endl;
    delay(10000);
    ledunit.off();
    std::cout << ledunit.getstate() << std::endl;
    delay(10000);
    ledunit.on();
    std::cout << ledunit.getstate() << std::endl;
    delay(10000);
    ledunit.off();
    std::cout << ledunit.getstate() << std::endl;
    delay(10000);
    ledunit.on();
    std::cout << ledunit.getstate() << std::endl;
    delay(10000);
    ledunit.off();
}

