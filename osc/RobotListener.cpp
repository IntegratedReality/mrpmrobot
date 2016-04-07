#include "RobotListener.h"

#include <iostream>
using namespace std;

void RobotListener::setup(RobotData *_data) {
	data = _data;
}

void RobotListener::ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndPoint) {
	try {
		if(std::strcmp(m.AddressPattern(), "/position") == 0) {
            cout << "hoge" << endl;
            
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			osc::int32 id;
			osc::int32 time;
			double x;
			double y;
			double theta;

			args >> id >> time >> x >> y >> theta >> osc::EndMessage;
			data[id].time = time;
			data[id].pos.x = x;
			data[id].pos.y = y;
			data[id].pos.theta = theta;

            cout << data[id].pos.x << endl;
		} else if (std::strcmp(m.AddressPattern(), "/main/robotstate") == 0) {
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			osc::int32 id;
			osc::int32 state;

			args >> id >> state >> osc::EndMessage;
			data[id].state = (EState)state;
		}
	} catch(osc::Exception& e) {
		std::cout << "error while parsing message :."
			<< m.AddressPattern() << ": " << e.what() << "\n";
	}
}
