/*
Robot's Main ProgramA of MRPM Project
Dept. of Precision Engneering, U-tokyo
Seimitsu Lab, Mayfes
*/

#include <iostream>
#include <array>

using namespace std;

#include "motor/motor.h"
#include "motor/drive.h"
#include "motor/operate.h"

#include "osc/RobotReceiver.h"

int main(void)
{
    RobotReceiver receiver;    
    long count = 0;
    receiver.init();
    while (1) {
       if (count != 30000000) {
           count++;
           continue;
       }
       RobotData data;
       data = receiver.getData(ID);
       cout << "x: " << data.pos.x << " ";
       cout << "y: " << data.pos.y << " ";
       cout << "theta: " << data.pos.theta << " ";
       cout << "drc: " << data.operation.direction << " ";
       cout << "shot: " << data.operation.shot << " ";
       cout << endl;
       count %= 30;
    }
    return 0;
}

