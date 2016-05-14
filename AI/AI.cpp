#include "AI.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

void AI::init(int _myid) {
    Myid = _myid;
    erou = DIRECT;
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
    if(estr == SIMPLE) developSimpleStrategy();
    //target = POPos[0];

    if(erou == DIRECT) developDirectRoute();
    else if(erou == DODGE) developDodgeRoute();
    else developRandomRoute();
}

void AI::setStrategy(EStrategy _estr){
    estr = _estr;
}

void AI::setRoute(ERoute _erou){
    erou = _erou;
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

void AI::developRandomRoute() {
	    this->operation.direction = (EDirection)(rand() % 9);
	    this->operation.shot = !(rand() % 5);
}

void AI::developDirectRoute() {
    //move to target directly
    double myposx = data[Myid].pos.x;
    double myposy = data[Myid].pos.y;
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
    EDirection mydir = NO_INPUT;
    bool myshot = true;

    if(dx * dx + dy * dy > DIST_TO_TARGET * DIST_TO_TARGET){    
        if(angle_diff >= LIMIT_TR_RIGHT) mydir = RIGHT;
        else if(angle_diff >= LIMIT_TOP_TR && angle_diff < LIMIT_TR_RIGHT) mydir = TOP_RIGHT;
        else if(angle_diff > LIMIT_TOP_TL && angle_diff < LIMIT_TOP_TR) mydir = TOP;
        else if(angle_diff >= LIMIT_TL_LEFT) mydir = TOP_LEFT;
        else mydir = LEFT;
    }else{
        if(angle_diff > LIMIT_TOP_TR) mydir = RIGHT;
        else if(angle_diff < LIMIT_TOP_TL) mydir = LEFT;
    }
    
	this->operation.direction = mydir;
	this->operation.shot = myshot;
}

void AI::developDodgeRoute() {
    Position mypos;
    mypos.x = data[Myid].pos.x;
    mypos.y = data[Myid].pos.y;
    mypos.theta = data[Myid].pos.theta;

    this->operation.direction = NO_INPUT;
    this->operation.shot = false;

    double minScore;
    for(int i = 1; i < 9; i++) {
        Position nextpos;
        nextpos.x = mypos.x + DIFF_MOVE * cos(mypos.theta + (M_PI / 4) * (i-1));
        nextpos.y = mypos.y + DIFF_MOVE * sin(mypos.theta + (M_PI / 4) * (i-1));
       
        double nextscore = 0;
        double dx = target.x - nextpos.x;
        double dy = target.y - nextpos.y;
        double diff2 = dx * dx + dy * dy;
        double targetscore = RATE_OF_TARGET * (1.0 - exp(- diff2 / RATE_OF_LENGTH_T));

        double obstscore = 0;
        for(int i = 0; i < NUM_OF_POINT_OBJ; i++){
            double dx = POPos[i].x - nextpos.x;
            double dy = POPos[i].y - nextpos.y;
            double diff2 = dx * dx + dy * dy;
            if(target.x != POPos[i].x) obstscore += RATE_OF_OBST * exp(- diff2 / RATE_OF_LENGTH_O);
        }
        for(int i = 0; i < NUM_OF_ROBOT; i++){
            double dx = data[i].pos.x - nextpos.x;
            double dy = data[i].pos.y - nextpos.y;
            double diff2 = dx * dx + dy * dy;
            if(i != Myid) obstscore += RATE_OF_OBST * exp(- diff2 / RATE_OF_LENGTH_O);
        }

        //Potensial function
        nextscore = (obstscore / RATE_OF_TARGET + 1) * targetscore; 
        //nextscore = obstscore + targetscore;
        if(i == 1) minScore = nextscore;
        if(nextscore <= minScore){
            if(dx * dx + dy * dy > DIST_TO_TARGET * DIST_TO_TARGET){
                if((EDirection)i == BOTTOM_RIGHT || (EDirection)i == BOTTOM) this->operation.direction = RIGHT;
                else if((EDirection)i == BOTTOM_LEFT) this->operation.direction = LEFT;
                else this->operation.direction = (EDirection)i;
                 
            }else{
                if((EDirection)i == TOP_RIGHT || (EDirection)i == RIGHT){
                    this->operation.direction = RIGHT;
                }else if((EDirection)i == TOP_LEFT || (EDirection)i == LEFT){
                    this->operation.direction = LEFT;
                }else{
                    double dx = target.x - mypos.x;
                    double dy = target.y - mypos.y;
                    double angle = atan(dy / dx);

                    if(dx < 0 && dy > 0) angle = M_PI + angle;
                    else if(dx < 0 && dy < 0) angle = -M_PI + angle;
                    
                    double angle_diff = angle - mypos.theta;
                    while(angle_diff > M_PI || angle_diff < -M_PI){
                        if(angle_diff > M_PI) angle_diff -= 2*M_PI;
                        else if(angle_diff < -M_PI) angle_diff += 2*M_PI;
                    }
                    
                    if(angle_diff > LIMIT_SHOT_ANGLE){
                        this->operation.direction = RIGHT;
                    }else if(angle_diff < (- LIMIT_SHOT_ANGLE)){ 
                        this->operation.direction = LEFT;
                    }else{
                        this->operation.direction = NO_INPUT;
                        this->operation.shot = true;
                    }
                }
            }
            minScore = nextscore;
        }
    }
}


void AI::developSimpleStrategy() {
    double myposx = data[Myid].pos.x;
    double myposy = data[Myid].pos.y;
    target = POPos[0];
    double mindiff = 0;
    for(int i = 0; i < NUM_OF_POINT_OBJ; i++){
        double dx = POPos[i].x - myposx;
        double dy = POPos[i].y - myposy;
        double diff2 = dx * dx + dy * dy;
        if(i == 0){
            mindiff = diff2;
        }else if(owner[i] != data[Myid].team){
            if(mindiff > diff2) mindiff = diff2;
            target = POPos[i];
        }
    }
    for(int i = 0; i < NUM_OF_ROBOT; i++){
        if(data[i].team == data[Myid].team) continue;
        if(data[i].state != NORMAL) continue;
        double dx = data[i].pos.x - myposx;
        double dy = data[i].pos.y - myposy;
        double diff2 = dx * dx + dy * dy;
        if(mindiff > diff2){
            mindiff = diff2;
            target = data[i].pos;
        }
    }
}



