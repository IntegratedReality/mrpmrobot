#include "RobotListner.h"

RobotListner::setup(RobotData &_data)
{
    data = &_data;
}

RobotListner::ProcessMsg(const osc::ReceivedMessage& m,
                         const IpEndpointName& remoteEndPoint)
{
    try{
        if(std::strcmp(m.AddressPattern(), "/main/robotposition") == 0){
            osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
            int id;
            int datatime;
            double x;
            double y;
            double theta;

            args >> id >> datatime >> x >> y >> theta >> osc::EndMessage;
            data[id].time = datatime;
            data[id].pos.x = x;
            data[id].pos.y = y;
            data[id].pos.theta = theta;
        }else if(std::strcmp(m.AddressPattern(), "/main/robotstate") == 0){
            osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
            int id;
            const char  *_state;

            args >> id >> state >> osc::EndMessage;
            data[id].state = _state;
        }
    }catch(osc::Exception& e){
        std::cout << "error while parsing message :."
                  << m.AddressPattern() << ": " << e.what() << "\n";
    }
}
