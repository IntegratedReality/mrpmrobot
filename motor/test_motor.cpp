#include "motor.h"
#include <iostream>
#include <wiringPi.h>
#include <random>
#include <array>

int main(void)
{
    std::array<MotorClass, 2> motor;
    motor.at(0).init(19, 26, true);
    motor.at(1).init(20, 21, true);
    int counter = 0;
    while (true) {
        motor.at(0).setMotor(MotorMode::Move, counter / 1000.0);
        std::cout << counter << std::endl;
        counter++;
        if (counter > 1000) {
            break;
        }
    }
    return 0;
}
