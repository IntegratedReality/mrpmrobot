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
    std::random_device rnd;
    std::uniform_int_distribution<> rnd_mode(0, 3);
    bool while_end_flag;
    while (!while_end_flag) {
            MotorMode mode;
            std::array<char, 2> command;
            std::cin >> command.at(0) >> command.at(1);
            for (int i = 0; i < 2; i++) {
                switch (command.at(i)) {
                case 'f':
                    mode = MotorMode::Forward;
                    break;
                case 'b':
                    mode = MotorMode::Back;
                    break;
                case 's':
                    mode = MotorMode::Stop;
                    break;
                case 'k':
                    mode = MotorMode::Brake;
                    break;
                case 'e':
                    while_end_flag = true;
                    mode = MotorMode::Stop;
                    break;
                default:
                    mode = static_cast<MotorMode>(rnd_mode(rnd));
                }
                motor.at(i).setMotor(mode);
                switch (motor.at(i).getMotorMode()) {
                case MotorMode::Forward:
                    std::cout << "Forward";
                    break;
                case MotorMode::Back:
                    std::cout << "Back";
                    break;
                case MotorMode::Stop:
                    std::cout << "Stop";
                    break;
                case MotorMode::Brake:
                    std::cout << "Brake";
                    break;
                default:
                    std::cout << "error!";
                }
                std::cout << '\t';
            }
            std::cout << std::endl;
            delay(1000);
    }
    return 0;
}
