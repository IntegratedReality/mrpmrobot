#include <cmath>
#include <array>
#include "drive.h"
#include "motor.h"

const double PI = 3.141592653589793;

bool Drive::setPostures(double now_x, double now_y, double now_theta, double dist_x, double dist_y, double dist_theta)
{
    this->dist_posture.at(0) = dist_x;
    this->dist_posture.at(1) = dist_y;
    this->dist_posture.at(2) = dist_theta;
    this->now_posture.at(0) = now_x;
    this->now_posture.at(1) = now_y;
    this->now_posture.at(2) = now_theta;
    return true;
}

bool Drive::move(DriveMoveMode mode)
{
    switch (mode) {
    case DriveMoveMode::MoveToPoint:
        moveToPoint();
        break;
    case DriveMoveMode::MoveToPosture:
        moveToPosture();
        break;
    default:
        return false;
    }
    return true;
}

void Drive::moveToPoint(void)
{
    std::array<double, 2> dist_vector;
    dist_vector.at(0) = dist_posture.at(0) - now_posture.at(0);
    dist_vector.at(1) = dist_posture.at(1) - now_posture.at(1);
    double dist_vector_length = std::sqrt(dist_vector.at(0) * dist_vector.at(0) + dist_vector.at(1) * dist_vector.at(1));
    dist_vector.at(0) /= dist_vector_length;
    dist_vector.at(1) /= dist_vector_length;
    double dist_angle = std::acos(dist_vector.at(0));
    bool turn_tobe_right = false;
    if (dist_vector.at(1) < 0) {
        turn_tobe_right = true;
    }
    if (dist_angle < PI / 6) {
        this->right_motor.setMotor(MotorMode::Forward);
        this->left_motor.setMotor(MotorMode::Back);
    } else if (dist_angle < PI / 2) {
        if (turn_tobe_right) {
            this->right_motor.setMotor(MotorMode::Brake);
            this->left_motor.setMotor(MotorMode::Forward);
        } else {
            this->right_motor.setMotor(MotorMode::Forward);
            this->left_motor.setMotor(MotorMode::Brake);
        }
    } else {
        if (turn_tobe_right) {
            this->right_motor.setMotor(MotorMode::Back);
            this->left_motor.setMotor(MotorMode::Forward);
        } else {
            this->right_motor.setMotor(MotorMode::Forward);
            this->left_motor.setMotor(MotorMode::Back);
        }
    }
}

void Drive::moveToPosture(void)
{
}
