#include <limits>
#include <algorithm>
#include <iostream>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include "operate.h"
#include "params.h"

namespace
{
    constexpr double PI = 3.141592653589793231;
}

bool Operate::setTargetPosition(double target_x, double target_y, double target_theta, double target_v)
{
    this->target_position.at(0) = target_x;
    this->target_position.at(1) = target_y;
    this->target_position.at(2) = target_theta;
    this->target_velocity = target_v;
    return true;
}

bool Operate::setNowPosition(double now_x, double now_y, double now_theta, double time)
{
    this->now_position.at(0) = now_x;
    this->now_position.at(1) = now_y;
    this->now_position.at(2) = now_theta;
    this->now_position.at(3) = time;
    this->drive.updateData(this->now_position.at(0), this->now_position.at(1), this->now_position.at(2), this->now_position.at(3));
    this->drive.updateDrive();
    return true;
}

bool Operate::operateUpdate(void)
{
    Eigen::Translation<double, 2> translation(-1 * this->target_position.at(0), -1 * this->target_position.at(1));
    Eigen::Rotation2Dd rotate(-1 * this->target_position.at(2));
    Eigen::Vector2d now_pos(this->now_position.at(0), this->now_position.at(1));
    now_pos = rotate * translation * now_pos;
    double now_theta = this->now_position.at(2) - this->target_position.at(2);
    double l = DISTANCE_BETWEEN_TWO_WHEEL * this->target_velocity / ((MAX_V_IN_SPEC - this->target_velocity) * 2);
    double alpha = now_pos.y() / l;
    alpha = std::max(-PI / 2, (std::min(alpha, PI / 2)));
    double omega_dest = - 3 * this->drive.getNowVelocity() / l * (alpha + now_theta);
    omega_dest = std::max(-1 * this->drive.getNowVelocity() / l, std::min(omega_dest, this->drive.getNowVelocity() / l));
    this->drive.setTarget(this->target_velocity, omega_dest);
    std::cout << this->target_velocity << "\t" << omega_dest << std::endl;
    this->drive.updateDrive();
    return true;
}
