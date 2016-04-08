#include "RobotReceiver.h"

void RobotReceiver::init() {
    listener.setup(data);
    std::thread th([this](){s.RunUntilSigInt();});
    th.detach();
}

void RobotReceiver::update() {
}

RobotData RobotReceiver::getData(int _id) {
    return data[_id];
}
