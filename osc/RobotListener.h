#pragma once 

#include <iostream>
#include <string>
#include <osc/OscReceiveElements>
#include <osc/OscPacketListener>
#include <ip/UdpSocket>

#include "../common/RobotData.h"
#include "../common/Const.h"

//Soon move these to Const.h
#define CAMPORT 7001
#define CTRLPORT 7002


class RobotListner : public osc:OscPacketListner {
public:
	virtual void ProcessMsg( const osc::ReceivedMessage& msg,
							 const IpEndpointName& remoteEndPoint ) {};
private:
	RobotData data[NUM_OF_ROBOT];
};
