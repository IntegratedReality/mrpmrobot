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
};
