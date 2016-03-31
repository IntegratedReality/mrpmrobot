#pragma once

#include <iostream>
#include <cstring>
#include <osc/OscReceiveElements>
#include <osc/OscPacketListener>
#include <ip/UdpSocket>

#include "../common/RobotData.h"
#include "../common/Const.h"

class RobotListener : public osc::OscPacketListner {
public:
	void setup(RobotData *_data);
	virtual void ProcessMessage(const osc::ReceivedMessage& msg, const IpEndpointName& remoteEndPoint );
private:
	RobotData *data;
};
