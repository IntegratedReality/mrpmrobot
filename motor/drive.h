#pragma once

#include <array>
#include "motor.h"

class DriveClass
{
    MotorClass right_motor;
    MotorClass left_motor;
    double target_velocity;
    double target_omega;
    // おそらく0から順に、x, y, theta, time(大杉)
    std::array<double, 4> now_status;
    std::array<double, 4> previous_status;
    double now_velocity;
    double now_omega;

	MotorMode mode;
public:
    DriveClass(MotorClass right_motor, MotorClass left_motor, double position_x, double position_y, double position_theta, double time) : right_motor(right_motor), left_motor(left_motor), target_velocity(0), target_omega(0), now_status{position_x, position_y, position_theta, time}, previous_status{position_x, position_y, position_theta, time}
    {}
    bool updateData(double position_x, double position_y, double position_theta, double time);
    bool setTarget(double target_velocity, double target_omega, MotorMode _mode = MotorMode::Move);
    bool updateDrive(void);
    double getTargetVelocity(void) const;
    double getTargetOmega(void) const;
    double getNowVelocity(void) const;
    double getNowOmega(void) const;
};
