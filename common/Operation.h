#pragma once

enum EDirection {
	NONE,
	TOP,
	TOP_RIGHT,
	RIGHT,
	BOTTOM_RIGHT,
	BOTTOM,
	BOTTOM_LEFT,
	LEFT,
	TOP_LEFT
};

struct Operation {
	EDirection direction;
	bool shot;
};

