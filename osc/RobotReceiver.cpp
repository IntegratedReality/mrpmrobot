#include "RobotReceiver.h"

void RobotReceiver::init() {
	for	(int i = 0; i < NUM_OF_ROBOT; i++) {
		data[i].init();
	}
	listener.setup(data, owner);
	std::thread th([this](){s.RunUntilSigInt();});
	th.detach();
}

RobotData RobotReceiver::getData(int _id) {
	return data[_id];
}

ETeam RobotReceiver::getPOOwner(int _id) {
	return owner[_id];
}

bool RobotReceiver::checkMessageReceived(void)
{
	return listener.checkMessageReceived();
}
