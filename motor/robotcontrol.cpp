#include <iostream>

#include "robotcontrol.h"

bool RobotControl::setTargetPosition(PositionInfo info, double target_v)
{
    return m_operate.setTargetPosition(info.x, info.y, info.theta, target_v);
}

bool RobotControl::setNowPosition(PositionInfo info, double time)
{
    return m_operate.setNowPosition(info.x, info.y, info.theta, time);
}

bool RobotControl::update(void)
{

    return m_operate.operateUpdate();
}

