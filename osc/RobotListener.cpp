#include "RobotListener.h"

#include <mutex>
#include <iostream>
using namespace std;

extern std::mutex mutex_obj;

void RobotListener::setup(RobotData *_data) {
    data = _data;
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

            args >> id >> time >> x >> y >> theta >> osc::EndMessage;
            data[id].time = time;
            data[id].pos.x = x;
            data[id].pos.y = y;
            data[id].pos.theta = theta;
        } else if (std::strcmp(m.AddressPattern(), "/main/robotstate") == 0) {
            osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
            osc::int32 id;
            osc::int32 state;

            args >> id >> state >> osc::EndMessage;
            data[id].state = (EState)state;
        } else if (std::strcmp(m.AddressPattern(), "/controller/operation") == 0) {
            osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
            osc::int32 drc;
            bool shot;

            args >> drc >> shot >> osc::EndMessage;
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
