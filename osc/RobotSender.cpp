#include "RobotSender.h"

#include <oscpack/osc/OscOutboundPacketStream.h>
#include <oscpack/ip/UdpSocket.h>

RobotSender::RobotSender():portname(0),socket(NULL)
{
}

void RobotSender::setup(std::string host, int port)
{
    socket = new UdpTransmitSocket(IpEndpointName(host.c_str(), port));
    
    this->hostname = host;
    this->portname = port;
}

void RobotSender::sendPos(int x, int y, int z)
{
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);

    p << osc::BeginBundleImmediate
        << osc::BeginMessage("/robot/pos")
        << x << y << z
        << osc::EndMessage
        << osc::EndBundle;

    socket->Send(p.Data(), p.Size());
}

void RobotSender::sendShot(int _id, bool _shot) {
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);

    p << osc::BeginBundleImmediate
        << osc::BeginMessage("/robot/shot")
        << _id
        << _shot
        << osc::EndMessage
        << osc::EndBundle;

    socket->Send(p.Data(), p.Size());
}
