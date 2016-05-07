#pragma once

#include "Position.h"
#include "EState.h"
#include "Operation.h"

struct RobotData {
	int id; // A:0~2 B:3~5
	Position pos;
	EState state;
	Operation operation;
	long time;
	void init() {
		id = 0;
		pos.x = 0;
		pos.y = 0;
		pos.theta = 0;
		state = (EState)0;
		operation.direction = (EDirection)0;
		operation.shot = false;
		time = 0;
	}
};
