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
    bool downcounterflag = false;
    bool next_end_flag = false;
    while (true) {
        motor.at(0).setMotor(MotorMode::Move, counter / 1000.0);
        std::cout << counter << std::endl;
        if (!downcounterflag) {
            counter++;
        } else {
            counter--;
        }
        if (counter > 1000) {
            downcounterflag = true;
        } 
        if (downcounterflag && counter < -1000) {
            next_end_flag = true;
            downcounterflag = false;
        }
        if (next_end_flag && counter == 1) {
            break;
        }
        delay(10);
    }
    return 0;
}
