#pragma once

enum ERoute {
    DIRECT,
    DODGE,
};
    
enum EStrategy {
    RANDOM,
    SIMPLE,
};

constexpr double LIMIT_TOP_TR = 0.2;
constexpr double LIMIT_TR_RIGHT = 1.0;
constexpr double LIMIT_TOP_TL = -0.2;
constexpr double LIMIT_TL_LEFT = -1.0;
constexpr double LIMIT_SHOT_ANGLE = 0.05;

constexpr int DIST_TO_TARGET = 300 + 125 + 100;
constexpr int DIFF_MOVE = 100; 
constexpr double RATE_OF_TARGET = 1.0;
constexpr double RATE_OF_OBST = 0.2;
constexpr double RATE_OF_LENGTH_T = 300 * 300;
constexpr double RATE_OF_LENGTH_O = 100 * 100;



