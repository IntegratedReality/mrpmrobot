#include <wiringPi.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "drive.h"
#include "params.h"

using namespace std;

bool DriveClass::updateData(double position_x, double position_y, double position_theta, double time)
{
    this->previous_status = this->now_status;
    this->now_status.at(0) = position_x;
    this->now_status.at(1) = position_y;
    this->now_status.at(2) = position_theta;
    this->now_status.at(3) = time;
    return true;
}

bool DriveClass::setTarget(double target_velocity, double target_omega, MotorMode _mode)
{
    this->target_velocity = target_velocity;
    this->target_omega = target_omega;
	this->mode = _mode;
    return true;
}

bool DriveClass::updateDrive(void)
{
    static bool first_update = true;
    static double sum_of_error_of_v = 0;
    static double previous_error_of_v = 0;
    static double sum_of_error_of_omega = 0;
    static double previous_error_of_omega = 0;
    double diff_of_time = this->now_status.at(3) - this->previous_status.at(3);

    // カメラ鯖からのフィードバック情報がない場合に発生する0除算回避用プロセス(大杉)
    if (diff_of_time == 0) {
        double max_vel = 0.3;
        double max_ome = 0.006;
        double next_right_duty = 0;
        double next_left_duty = 0;
        double vel_duty = target_velocity / max_vel;
        double ome_duty = target_omega / max_ome * 0.5;
        next_right_duty = vel_duty + ome_duty;
        next_left_duty = vel_duty - ome_duty;
        this->right_motor.setMotor(mode, next_right_duty);
        this->left_motor.setMotor(mode, next_left_duty);
        return true;
    }

    double now_velocity_x = (this->now_status.at(0) - this->previous_status.at(0)) / diff_of_time;
    double now_velocity_y = (this->now_status.at(1) - this->previous_status.at(1)) / diff_of_time;
    this->now_velocity = std::sqrt(now_velocity_x * now_velocity_x + now_velocity_y * now_velocity_y);
    double error_of_velocity = this->target_velocity - now_velocity;
    double next_average_duty = 0;
    next_average_duty += error_of_velocity * DRIVE_V_GAIN_P;
    sum_of_error_of_v += error_of_velocity * diff_of_time;
    next_average_duty += sum_of_error_of_v * DRIVE_V_GAIN_I;
    if (!first_update) {
        next_average_duty += (error_of_velocity - previous_error_of_v) / diff_of_time * DRIVE_V_GAIN_D;
    }
    this->now_omega = (this->now_status.at(2) - this->previous_status.at(2)) / diff_of_time;
    double error_of_omega = this->target_omega - now_omega;
    double next_diff_duty = 0;
    next_diff_duty += error_of_omega * DRIVE_OMEGA_GAIN_P;
    sum_of_error_of_omega += error_of_omega;
    next_diff_duty += sum_of_error_of_omega * DRIVE_OMEGA_GAIN_I;
    if (!first_update) {
        next_diff_duty += (error_of_omega - previous_error_of_omega) / diff_of_time * DRIVE_OMEGA_GAIN_D;
    }
    double next_right_duty = 0;
    double next_left_duty = 0;
    while (true) {
        next_right_duty = next_average_duty + next_diff_duty;
        next_left_duty = next_average_duty - next_diff_duty;
        if (-1 <= next_right_duty && next_right_duty <= 1 && -1 <= next_left_duty && next_left_duty <= 1) {
            break;
        } else {
            double over_max = std::max(std::abs(next_right_duty), std::abs(next_left_duty));
            next_average_duty /= over_max;
            next_diff_duty /= over_max;
        }
    } 
    this->right_motor.setMotor(MotorMode::Move, next_right_duty);
    this->left_motor.setMotor(MotorMode::Move, next_left_duty);
    previous_error_of_v = error_of_velocity;
    previous_error_of_omega = error_of_omega;
    first_update = false;
    return true;
}

double DriveClass::getTargetVelocity(void) const
{
    return this->target_velocity;
}

double DriveClass::getTargetOmega(void) const
{
    return this->target_omega;
}

double DriveClass::getNowVelocity(void) const
{
    return this->now_velocity;
}

double DriveClass::getNowOmega(void) const
{
    return this->now_omega;
}
