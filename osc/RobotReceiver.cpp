#include "RobotReceiver.h"

void RobotReceiver::init() {
	listener.setup(data);
    s.RunUntilSigInt();
}

void RobotReceiver::update() {
}

RobotData RobotReceiver::getData(int _id) {
	return data[_id];
}
