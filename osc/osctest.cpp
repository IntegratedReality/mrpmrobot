#include <iostream>
#include <string>
#include "OscSender.h"

int main(void)
{
    std::string host = "milktea.local";
    int port = 8000;
    OscSender sender;
    sender.setup(host, port);
    sender.sendPos(100, 100, 100);
}
