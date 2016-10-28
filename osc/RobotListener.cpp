#include "RobotListener.h"

#include <mutex>
#include <iostream>
#include <array>
using namespace std;

extern std::mutex mutex_obj;

RobotListener::RobotListener(RobotData& _data, std::array<bool, 9>& _permissions):
  data(_data),
  permissions(_permissions)
{
}

void RobotListener::ProcessMessage(const osc::ReceivedMessage& m, __attribute__((unused)) const IpEndpointName& remoteEndPoint) {
	try {
		if(std::strcmp(m.AddressPattern(), "/main/toRobot") == 0) {
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			//osc::int32 id;
			osc::int32 time;
			double x;
			double y;
			double theta;
			//double HP;
			//double EN;
			//osc::int32 state;

			//args >> id >> time >> x >> y >> theta >> HP >> EN >> state >> osc::EndMessage;
      args >> time >> x >> y >> theta;
      for(auto& e: permissions){
        args >> e;
      }
      args >> osc::EndMessage;
			//data.id = id;
			data.time = time;
			//cout << time << endl;
			data.pos.x = x;
			data.pos.y = y;
			data.pos.theta = theta;
			//data.HP = HP;
			//data.EN = EN;
			//data.state = (EState)state;
			//data.team = id < 3 ? TEAM_A : TEAM_B;
		}
    /* else if (std::strcmp(m.AddressPattern(), "/main/poowner") == 0) {
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			osc::int32 id;
			osc::int32 team;

			args >> id >> team >> osc::EndMessage;
			owner[id] = (ETeam)team;
		} */ 
    else if (std::strcmp(m.AddressPattern(), "/ctrlr/operation") == 0) {
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			//bool isAI;
			osc::int32 drc;
			//bool shot;

			//args >> isAI >> drc >> shot >> osc::EndMessage;
      args >> drc >> osc::EndMessage;
			//data.isAI = isAI;
			data.operation.direction = (EDirection)drc;
			//data.operation.shot = shot;
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
