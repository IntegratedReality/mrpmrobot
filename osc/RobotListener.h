#pragma once

#include <iostream>
#include <cstring>
#include <oscpack/osc/OscReceivedElements.h>
#include <oscpack/osc/OscPacketListener.h>
#include <oscpack/ip/UdpSocket.h>

#include "../common/RobotData.h"
#include "../common/Const.h"

class RobotListener : public osc::OscPacketListener {
	public:
		RobotListener(RobotData& _data, std::array<bool, 9>& _permissions);
		virtual void ProcessMessage(const osc::ReceivedMessage& msg, const IpEndpointName& remoteEndPoint );
		bool checkMessageReceived(void);
	private:
		RobotData& data;
    std::array<bool, 9>& permissions;
		//ETeam *owner;
		bool m_message_received;
};
