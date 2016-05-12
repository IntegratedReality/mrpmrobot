/*
	 Robot's Main ProgramA of MRPM Project
	 Dept. of Precision Engneering, U-tokyo
	 Seimitsu Lab, Mayfes
	 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <array>
#include <thread>
#include <mutex>

using namespace std;

#include "ledunit/ledunit.h"

#include "motor/robotcontrol.h"
#include "motor/drive.h"
#include "motor/params.h"

#include "osc/RobotReceiver.h"
#include "osc/RobotSender.h"

#include "AI/AI.h"

#include "wiringPi.h"

std::mutex mutex_obj;

extern int ID;

void checkMovable(Position _pos, bool &_F, bool &_B);
double distance(Position _p1, Position _p2);
bool hoge(double _ax, double _ay, double _bx, double _by);

AI ai;

int main(int argc, char **argv)
{
	if (argc == 2) ID = atoi(argv[1]);
	else {
		cout << "コマンドライン引数でロボットのIDを指定してください。m(__)m" << endl;
		return 0;
	}

	ai.init(ID);

	wiringPiSetupGpio();
	LedUnit led_unit(24);
	led_unit.on();

	RobotReceiver receiver;
	receiver.init();
	RobotSender sender;
	sender.setup("Coconuts.local", 8000);

	while (!receiver.checkMessageReceived());

	DriveClass drive(MotorClass(22, 27, false), MotorClass(17, 18, true), receiver.getData(ID).pos.x, receiver.getData(ID).pos.y, receiver.getData(ID).pos.theta, receiver.getData(ID).time);

	std::thread robot_control_thread([&](){
			while (true) {
			while (!receiver.checkMessageReceived());
			mutex_obj.lock();
			drive.updateData(receiver.getData(ID).pos.x, receiver.getData(ID).pos.y, receiver.getData(ID).pos.theta, receiver.getData(ID).time);
			drive.updateDrive();
			if (ID < 3) sender.sendShot(ID, receiver.getData(ID).operation.shot);
			mutex_obj.unlock();
			}
			});

	long count = 0;
	while (1) {
		// ここを弄るといいらしい
		RobotData data;
		data = receiver.getData(ID);

		if (ID >= 3) {
			sender.sendShot(ID, ai.getOperation().shot);
			for (int i = 0; i < 6; i++) {
				ai.setRobotData(i, receiver.getData(i));
			}
			for (int i = 0; i < 3; i++) {
				ai.setPOOwner(i, receiver.getPOOwner(i));
			}
			ai.update();
		}

		double max_v = 0.1, max_omega = 0.001;
		double v = 0, omega = 0;

		// オーバードライブ防止処理
		bool F, B;
		checkMovable(data.pos, F, B);

		bool MoveSURUNO = true;

		switch (ID < 3 ? data.operation.direction : ai.getOperation().direction) {
			case NO_INPUT:
				break;
			case TOP:
				v = (double)F * max_v;
				MoveSURUNO = F;
				break;
			case TOP_RIGHT:
				v = (double)F * max_v;
				omega = -0.6 * max_omega;
				MoveSURUNO = F;
				break;
			case RIGHT:
				omega = -4 * max_omega;
				break;
			case BOTTOM_RIGHT:
				v = -((double)B * max_v);
				omega = 0.6 * max_omega;
				MoveSURUNO = B;
				break;
			case BOTTOM:
				v = -((double)B * max_v);
				MoveSURUNO = B;
				break;
			case BOTTOM_LEFT:
				v = -((double)B * max_v);
				omega = -0.6 * max_omega;
				MoveSURUNO = B;
				break;
			case LEFT:
				omega = 4 * max_omega;
				break;
			case TOP_LEFT:
				v = (double)F * max_v;
				omega = 0.6 * max_omega;
				MoveSURUNO = F;
				break;
		}
		mutex_obj.lock();
		drive.setTarget(v, omega, (MoveSURUNO ? MotorMode::Move : MotorMode::Brake));
		mutex_obj.unlock();
		// ここまでを弄る

		if (count != 300000) {
			count++;
			continue;
		}
		cout << F << B << endl;
		cout << "v: " << v << " ";
		cout << "omega: " << omega << " ";
		cout << "x: " << data.pos.x << " ";
		cout << "y: " << data.pos.y << " ";
		cout << "theta: " << data.pos.theta << " ";
		cout << "time:" << data.time << " ";
		cout << "drc: " << (ID < 3 ? data.operation.direction : ai.getOperation().direction) << " ";
		cout << "shot: " << (ID < 3 ? data.operation.shot : ai.getOperation().shot) << " ";
		cout << endl;
		count = 0;
	}
	return 0;
}

Position p1(1800 / 4., 2700 / 4., 0);
Position p2(2 * 1800 / 4., 2 * 2700 / 4., 0);
Position p3(3 * 1800 / 4., 3 * 2700 / 4., 0);

void checkMovable(Position _pos, bool &_F, bool &_B) {
	double vx = cos(_pos.theta), vy = sin(_pos.theta);
	_F = true;
	_B = true;

	// フィールド上辺
	if (_pos.y < 130) {
		if (vy < 0) _F = false; 
		else _B = false;
	} 
	// 右辺
	if (_pos.x > 1800 - 130) {
		if (vx > 0) _F = false; 
		else _B = false;
	}
	// 下辺
	if (_pos.y > 2700 - 130) {
		if (vy > 0) _F = false; 
		else _B = false;
	}
	// 左辺
	if (_pos.x < 130) {
		if (vx < 0) _F = false; 
		else _B = false;
	}
	// ポイントオブジェクト1
	if (distance(_pos, p1) < 125 + 100 + 30) {
		if (hoge(vx, vy, p1.x - _pos.x, p1.y - _pos.y)) _F = false;
		else _B = false;
	}
	// ポイントオブジェクト2
	if (distance(_pos, p2) < 125 + 100 + 30) {
		if (hoge(vx, vy, p2.x - _pos.x, p2.y - _pos.y)) _F = false;
		else _B = false;
	}
	// ポイントオブジェクト3
	if (distance(_pos, p3) < 125 + 100 + 30) {
		if (hoge(vx, vy, p3.x - _pos.x, p3.y - _pos.y)) _F = false;
		else _B = false;
	}
}

double distance(Position _p1, Position _p2) {
	return sqrt(pow(_p1.x - _p2.x, 2.) + pow(_p1.y - _p2.y, 2.));
}

// まじホゲって感じ 
bool hoge(double _ax, double _ay, double _bx, double _by) {
	return (_ax * _bx + _ay * _by) > 0;
}
