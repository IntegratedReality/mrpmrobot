#include "RobotListener.h"

#include <mutex>
#include <iostream>
using namespace std;

extern std::mutex mutex_obj;

void RobotListener::setup(RobotData *_data, ETeam *_owner) {
	data = _data;
	owner = _owner;
}

void RobotListener::ProcessMessage(const osc::ReceivedMessage& m, __attribute__((unused)) const IpEndpointName& remoteEndPoint) {
	try {
		if(std::strcmp(m.AddressPattern(), "/main/position") == 0) {
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			osc::int32 id;
			osc::int32 time;
			double x;
			double y;
			double theta;
			double HP;
			double EN;
			osc::int32 state;

			args >> id >> time >> x >> y >> theta >> HP >> EN >> state >> osc::EndMessage;
			data[id].id = id;
			data[id].time = time;
			//cout << time << endl;
			data[id].pos.x = x;
			data[id].pos.y = y;
			data[id].pos.theta = theta;
			data[id].HP = HP;
			data[id].EN = EN;
			data[id].state = (EState)state;
			data[id].team = id < 3 ? TEAM_A : TEAM_B;
		} else if (std::strcmp(m.AddressPattern(), "/main/poowner") == 0) {
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			osc::int32 id;
			osc::int32 team;

			args >> id >> team >> osc::EndMessage;
			owner[id] = (ETeam)team;
		} else if (std::strcmp(m.AddressPattern(), "/controller/operation") == 0) {
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			bool isAI;
			osc::int32 drc;
			bool shot;

			args >> isAI >> drc >> shot >> osc::EndMessage;
			data[ID].isAI = isAI;
			data[ID].operation.direction = (EDirection)drc;
			data[ID].operation.shot = shot;
		}
	} catch(osc::Exception& e) {
		std::cout << "error while parsing message :."
			<< m.AddressPattern() << ": " << e.what() << "\n";
	}
	mutex_obj.lock();
	m_message_received = true;
	mutex_obj.unlock();
}

bool RobotListener::checkMessageReceived(void)
{
	mutex_obj.lock();
	//cout << "Message:lock" << endl;
	if (m_message_received) {
		m_message_received = false;
		mutex_obj.unlock();
		//cout << "Message:unlock" << endl;
		return true;
	} else {
		mutex_obj.unlock();
		//cout << "Message:unlock" << endl;
		return false;
	}
}
