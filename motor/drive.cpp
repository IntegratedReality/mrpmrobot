#include <wiringPi.h>
#include <cmath>
#include "drive.h"
#include "params.h"

DriveClass::~DriveClass()
{
    this->setTarget(0, 0);
    this->updateDrive();
}

bool DriveClass::updateData(double position_x, double position_y, double position_theta, double time)
{
    this->previous_status = this->now_status;
    this->now_status.at(0) = position_x;
    this->now_status.at(1) = position_y;
    this->now_status.at(2) = position_theta;
    this->now_status.at(3) = time;
    return true;
}

bool DriveClass::setTarget(double target_velocity, double target_omega)
{
    this->target_velocity = target_velocity;
    this->target_omega = target_omega;
    return true;
}

bool DriveClass::updateDrive(void)
{
    static double sum_of_error_of_v = 0;
    static double previous_error_of_v = 0;
    static double sum_of_error_of_omega = 0;
    static double previous_error_of_omega = 0;
    double diff_of_time = this->now_status.at(3) - this->previous_status.at(3);
    double now_velocity_x = (this->now_status.at(0) - this->previous_status.at(1)) / diff_of_time;
    double now_velocity_y = (this->now_status.at(0) - this->previous_status.at(1)) / diff_of_time;
    double now_velocity = std::sqrt(now_velocity_x * now_velocity_x + now_velocity_y * now_velocity_y);
    double error_of_velocity = this->target_velocity - now_velocity;
    double next_average_duty = 0;
    next_average_duty += error_of_velocity * DRIVE_V_GAIN_P;
    sum_of_error_of_v += error_of_velocity;
    next_average_duty += sum_of_error_of_v * DRIVE_V_GAIN_I;
    next_average_duty += (error_of_velocity - previous_error_of_v) * DRIVE_V_GAIN_D;
    double now_omega = (this->now_status.at(2) - this->previous_status.at(2)) / diff_of_time;
    double error_of_omega = this->target_omega - now_omega;
    double next_diff_duty = 0;
    next_diff_duty += error_of_omega * DRIVE_OMEGA_GAIN_P;
    sum_of_error_of_omega += error_of_omega;
    next_diff_duty += sum_of_error_of_omega * DRIVE_OMEGA_GAIN_I;
    next_diff_duty += (error_of_omega - previous_error_of_omega) * DRIVE_OMEGA_GAIN_D;
    this->right_motor.setMotor(MotorMode::Move, next_average_duty + next_diff_duty);
    this->left_motor.setMotor(MotorMode::Move, next_average_duty - next_diff_duty);
    previous_error_of_v = error_of_velocity;
    previous_error_of_omega = error_of_omega;
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
