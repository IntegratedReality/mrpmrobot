#pragma once

#include <iostream>
#include <string>

#include "oscpack/osc/OscTypes.h"
#include "oscpack/osc/OscOutboundPacketStream.h"
#include "oscpack/ip/UdpSocket.h"

#define OUTPUT_BUFFER_SIZE 1024

class OscSender{
public:
    OscSender();
    void setup(std::string host, int port);
    void sendPos(int x, int y, int z);

private:
    std::string hostname;
    int portname;
    UdpTransmitSocket* socket;
};
