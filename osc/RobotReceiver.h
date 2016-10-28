#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <array>
#include <oscpack/osc/OscReceivedElements.h>
#include <oscpack/osc/OscPacketListener.h>
#include <oscpack/ip/UdpSocket.h>

#include "../common/RobotData.h"
#include "../common/Const.h"
#include "RobotListener.h"

const int PORT_ROBOT{8000};

class RobotReceiver {
	public:
		RobotReceiver() {}
		void init();
		void update();
		RobotData getData();
    std::array<bool, 9> getPermissions();
		//ETeam getPOOwner(int _id);
		bool checkMessageReceived(void);
	private:
		std::thread th;

    std::unique_ptr<RobotListener> listener_ptr;

    std::unique_ptr<UdpListeningReceiveSocket> s;
		RobotData data;
    std::array<bool, 9> permissions;
		//ETeam owner[3];
};
