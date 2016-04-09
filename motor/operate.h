#pragma once

#include <array>

#include "drive.h"

class Operate
{
    DriveClass drive;
    std::array<double, 3> target_position;
    double target_velocity;
    std::array<double, 4> now_position;
public:
    Operate(DriveClass drive) : drive(drive)
    {}
    bool setTargetPosition(double target_x, double target_y, double target_theta, double target_v);
    bool setNowPosition(double now_x, double now_y, double now_theta, double time);
    bool operateUpdate(void);
};
