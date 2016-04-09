#pragma once

#include <array>

#include "operate.h"

struct MotorInfo
{
    std::array<int, 2> mot1_pins;
    std::array<int, 2> mot2_pins;
    bool mot1_direct;
    bool mot2_direct;
};

struct PositionInfo
{
    double x;
    double y;
    double theta;
};

class RobotControl
{
    Operate m_operate;
public:
    RobotControl(MotorInfo motor_info, PositionInfo place_info, double time) : m_operate(DriveClass(MotorClass(motor_info.mot1_pins.at(0), motor_info.mot2_pins.at(1), motor_info.mot1_direct), MotorClass(motor_info.mot2_pins.at(0), motor_info.mot2_pins.at(1), motor_info.mot2_direct), place_info.x, place_info.y, place_info.theta, time))
    {}
    bool setTargetPosition(PositionInfo info, double target_v);
    bool setNowPosition(PositionInfo info, double time);
    bool update(void);
};
