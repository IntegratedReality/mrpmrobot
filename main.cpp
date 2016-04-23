/*
   Robot's Main ProgramA of MRPM Project
   Dept. of Precision Engneering, U-tokyo
   Seimitsu Lab, Mayfes
 */

#include <iostream>
#include <array>
#include <thread>
#include <mutex>

using namespace std;

#include "ledunit/ledunit.h"

#include "motor/robotcontrol.h"
#include "motor/drive.h"
#include "motor/params.h"

#include "osc/RobotReceiver.h"

#include "wiringPi.h"

std::mutex mutex_obj;

int main(void)
{
    wiringPiSetupGpio();
    LedUnit led_unit(24);
    led_unit.on();
    RobotReceiver receiver;    
    long count = 0;
    receiver.init();
    while (!receiver.checkMessageReceived());
    //RobotControl robot_control({{3, 4}, {17, 18}, true, false}, {receiver.getData(0).pos.x, receiver.getData(0).pos.y, receiver.getData(0).pos.theta}, receiver.getData(0).time);
    DriveClass drive(MotorClass(22, 27, false), MotorClass(17, 18, false), receiver.getData(0).pos.x, receiver.getData(0).pos.y, receiver.getData(0).pos.theta, receiver.getData(0).time);
    std::cout << "x:" << receiver.getData(0).pos.x << " " << receiver.getData(0).time << std::endl; //これを消すと動かなくなる
    std::thread robot_control_thread([&](){
            while (true) {
            while (!receiver.checkMessageReceived());
            //std::cout << "x:" << receiver.getData(0).pos.x << " " << receiver.getData(0).time << std::endl;
            mutex_obj.lock();
            //robot_control.setNowPosition({receiver.getData(0).pos.x, receiver.getData(0).pos.y, receiver.getData(0).pos.theta}, receiver.getData(0).time);
            //robot_control.update();
            drive.updateData(receiver.getData(0).pos.x, receiver.getData(0).pos.y, receiver.getData(0).pos.theta, receiver.getData(0).time);
            drive.updateDrive();
            mutex_obj.unlock();
            }
            });
    while (1) {
        if (count != 30000000) {
            count++;
            continue;
        }

        // ここを弄るといいらしい
        RobotData data;
        data = receiver.getData(ID);

        double max_v = 0.2, max_omega = 0.005;
        double v = 0, omega = 0;
        switch (data.operation.direction) {
            case TOP:
                v = max_v;
                break;
        }
        //mutex_obj.lock();
        //drive.setTarget(v, omega);
        //mutex_obj.unlock();
        // ここまでを弄る

        cout << "v: " << v << " ";
        cout << "omega: " << omega << " ";
        cout << "x: " << data.pos.x << " ";
        cout << "y: " << data.pos.y << " ";
        cout << "theta: " << data.pos.theta << " ";
        cout << "time:" << data.time << " ";
        cout << "drc: " << data.operation.direction << " ";
        cout << "shot: " << data.operation.shot << " ";
        cout << endl;
        count = 0;
    }
    return 0;
}

