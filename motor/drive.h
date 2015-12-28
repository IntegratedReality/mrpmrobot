#pragma once

#include <array>

#include "motor.h"

enum class DriveMoveMode
{
    MoveToPoint,
    MoveToPosture
};

class Drive
{
    MotorClass right_motor;
    MotorClass left_motor;
    std::array<double, 3> dist_posture;
    std::array<double, 3> now_posture;
    void moveToPoint(void);
    void moveToPosture(void);
public:
    Drive(MotorClass right_motor, MotorClass left_motor) : right_motor(right_motor), left_motor(left_motor)
    {}
    bool setPostures(double now_x, double now_y, double now_theta, double dist_x, double dist_y, double dist_theta);
    bool move(DriveMoveMode mode);
};
