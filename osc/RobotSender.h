#pragma once

#include <iostream>
#include <string>

#include "osc/OscTypes.h"
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#define OUTPUT_BUFFER_SIZE 1024

class RobotSender{
    public:
        RobotSender();
        void setup(std::string host, int port);
        void sendPos(int x, int y, int z);
        void sendShot(int _id, bool _shot);

    private:
        std::string hostname;
        int portname;
        UdpTransmitSocket* socket;
};
