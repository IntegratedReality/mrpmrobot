#pragma once

#include <iostream>
#include <cstring>
#include <osc/OscReceivedElements.h>
#include <osc/OscPacketListener.h>
#include <ip/UdpSocket.h>

#include "../common/RobotData.h"
#include "../common/Const.h"

class RobotListener : public osc::OscPacketListener {
public:
	void setup(RobotData *_data);
	virtual void ProcessMessage(const osc::ReceivedMessage& msg, const IpEndpointName& remoteEndPoint );
private:
	RobotData *data;
};
