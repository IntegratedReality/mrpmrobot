#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <oscpack/osc/OscReceivedElements.h>
#include <oscpack/osc/OscPacketListener.h>
#include <oscpack/ip/UdpSocket.h>

#include "../common/RobotData.h"
#include "../common/Const.h"
#include "RobotListener.h"

#define PORT 8000

class RobotReceiver {
	public:
		RobotReceiver() : s(IpEndpointName(IpEndpointName::ANY_ADDRESS, PORT), &listener) {}
		void init();
		void update();
		RobotData getData(int _id);
		ETeam getPOOwner(int _id);
		bool checkMessageReceived(void);
	private:
		std::thread th;
		RobotListener listener;
		UdpListeningReceiveSocket s;
		RobotData data[NUM_OF_ROBOT];
		ETeam owner[3];
};
