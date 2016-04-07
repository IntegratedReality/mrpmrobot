#pragma once

#include <iostream>
#include <string>
#include <osc/OscReceivedElements.h>
#include <osc/OscPacketListener.h>
#include <ip/UdpSocket.h>

#include "../common/RobotData.h"
#include "../common/Const.h"
#include "RobotListener.h"

#define PORT 8000

class RobotReceiver {
	public:
		void init();
		void update();
		RobotData getData(int _id);
		RobotReceiver() : s(IpEndpointName(IpEndpointName::ANY_ADDRESS, PORT), &listener) {}
	private:
		RobotListener listener;
		UdpListeningReceiveSocket s;
		RobotData data[NUM_OF_ROBOT];
};
