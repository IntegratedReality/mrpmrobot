#include "AI.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

void AI::init(int _myid) {
	Myid = _myid;
	estr = SIMPLE;
	POPos[0].x = POINT_OBJ_0_X;
	POPos[0].y = POINT_OBJ_0_Y;
	POPos[1].x = POINT_OBJ_1_X;
	POPos[1].y = POINT_OBJ_1_Y;
	POPos[2].x = POINT_OBJ_2_X;
	POPos[2].y = POINT_OBJ_2_Y;
	target = POPos[0];
}

void AI::update() {
	developStrategy();

	if(estr == RANDOM){
		// 適当乱数AI
		this->operation.direction = (EDirection)(rand() % 9);
		this->operation.shot = !(rand() % 5);
	}else{
		//move to target directly
		int myposx = data[Myid].pos.x;
		int myposy = data[Myid].pos.y;
		double myposth = data[Myid].pos.theta;
		double dx = target.x - myposx;
		double dy = target.y - myposy;
		double angle = atan(dy / dx);
		if(dx < 0 && dy > 0) angle = M_PI + angle;
		else if(dx < 0 && dy < 0) angle = -M_PI + angle;

		double angle_diff = angle - myposth;
		while(angle_diff > M_PI || angle_diff < -M_PI){
			if(angle_diff > M_PI) angle_diff -= 2*M_PI;
			else if(angle_diff < -M_PI) angle_diff += 2*M_PI;
		}
		//for debug robot motion
		//std::cout << "x:" << myposx << " y:" <<  myposy << " theta:" << myposth
		//          << " ang:" << angle <<  " da:" << angle_diff << std::endl;
		EDirection mydir = NO_INPUT;
		bool myshot = true;

		if(angle_diff >= LIMIT_TR_RIGHT) mydir = RIGHT;
		else if(angle_diff >= LIMIT_TOP_TR && angle_diff < LIMIT_TR_RIGHT) mydir = TOP_RIGHT;
		else if(angle_diff > LIMIT_TOP_TL && angle_diff < LIMIT_TOP_TR) mydir = TOP;
		else if(angle_diff >= LIMIT_TL_LEFT) mydir = TOP_LEFT;
		else mydir = LEFT;

		this->operation.direction = mydir;
		this->operation.shot = myshot;
	}
}

void AI::setStrategy(EStrategy _estr){
	estr = _estr;
}

void AI::setRobotData(int _id, RobotData _data) {
	data[_id] = _data;
}

void AI::setPOOwner(int _id, ETeam _owner) {
	owner[_id] = _owner;
}

Operation AI::getOperation() {
	return operation;
}

void AI::developStrategy() {
	int myposx = data[Myid].pos.x;
	int myposy = data[Myid].pos.y;
	target = POPos[0];
	//std::cout << "ROBOT:" << Myid << " ";
	int mindiff = 0;
	for(int i = 0; i < NUM_OF_POINT_OBJ; i++){
		int dx = POPos[i].x - myposx;
		int dy = POPos[i].y - myposy;
		int diff2 = dx * dx + dy * dy;
		//std::cout << "diff:" << diff2 << std::endl;
		if(i == 0){
			mindiff = diff2;
		}else if(mindiff > diff2 && owner[i] != data[Myid].team){
			mindiff = diff2;
			target = POPos[i];
		}
	}
	for(int i = 0; i < NUM_OF_ROBOT; i++){
		if(data[i].team == data[Myid].team) continue;
		int dx = data[i].pos.x - myposx;
		int dy = data[i].pos.y - myposy;
		int diff2 = dx * dx + dy * dy;
		//std::cout << "diff:" << diff2 << std::endl;
		if(mindiff > diff2){
			mindiff = diff2;
			target = data[i].pos;
		}
	} 
}
