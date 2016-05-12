#pragma once

#include "../common/Const.h"
#include "../common/Operation.h"
#include "../common/RobotData.h"
#include "../common/Position.h"
#include "AIParams.h"

class AI {
    public:
        void init(int _myid);
        void setStrategy(EStrategy _estr);
        void setRoute(ERoute _erou);

		// 基底クラスで抽出するかも
		void update();
		void setRobotData(int _id, RobotData _data);
		void setPOOwner(int _id, ETeam _owner);
		Operation getOperation();

        void developRandomRoute();
        void developDirectRoute();
        void developDodgeRoute();
	
        void developSimpleStrategy();

	protected:
		Operation operation;
		RobotData data[NUM_OF_ROBOT];
		ETeam owner[NUM_OF_POINT_OBJ];

    private:
        int Myid;
        ERoute erou;
        EStrategy estr;
        Position target;
        Position POPos[NUM_OF_POINT_OBJ];
};
