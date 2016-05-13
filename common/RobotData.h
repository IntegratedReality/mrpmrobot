#pragma once

#include "Position.h"
#include "ETeam.h"
#include "EState.h"
#include "EItem.h"
#include "Operation.h"

struct RobotData {
	int id; // A:0~2 B:3~5
	ETeam team;
	EState state;
	EItem item;
	Position pos;
	Operation operation;
	long time;
	double HP;
	double EN;
	bool isAI;
	void init() {
		id = 0;
		pos.x = 0;
		pos.y = 0;
		pos.theta = 0;
		state = (EState)0;
		operation.direction = (EDirection)0;
		operation.shot = false;
		time = 0;
		isAI = false;
	}
};
