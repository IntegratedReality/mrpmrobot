#pragma once

#include <iostream>
#include <string>
#include <osc/OscReceiveElements>
#include <osc/OscPacketListener>
#include <ip/UdpSocket  >

#include "../common/RobotData.h"
#include "../common/Const.h"
#include "RobotListner.h"

class RobotReceiver {
public:
    void init();
    void update();
    RobotData getRobotData(int robotnumber) const;
private:
    RobotListner listener;
    UdpListeningReceiveSocket s(IpEndpointName(IpEndpointName::ANY_ADDRESS, RECEIVEPORT));
	RobotData data[NUM_OF_ROBOT];
};
