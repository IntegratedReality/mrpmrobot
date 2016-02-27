#pragma once

#include <array>
#include "motor.h"

class DriveClass
{
    MotorClass right_motor;
    MotorClass left_motor;
    double target_velocity;
    double target_omega;
    std::array<double, 4> now_status;
    std::array<double, 4> previous_status;
public:
    DriveClass(MotorClass& right_motor, MotorClass& left_motor, double position_x, double position_y, double position_theta, double time) : right_motor(right_motor), left_motor(left_motor), target_velocity(0), target_omega(0), now_status{position_x, position_y, position_theta, time}, previous_status(now_status)
    {}
    ~DriveClass();
    bool updateData(double position_x, double position_y, double position_theta, double time);
    bool setTarget(double target_velocity, double target_omega);
    bool updateDrive(void);
    double getTargetVelocity(void) const;
    double getTargetOmega(void) const;
};
