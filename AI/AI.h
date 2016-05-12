#pragma once

#include "../common/Const.h"
#include "../common/Operation.h"
#include "../common/RobotData.h"
#include "../common/Position.h"
#include "EStrategy.h"
#include "AIParams.h"

class AI {
	public:
		void init(int _myid);
		void setStrategy(EStrategy _estr);

		// 基底クラスで抽出するかも
		void update();
		void setRobotData(int _id, RobotData _data);
		void setPOOwner(int _id, ETeam _owner);
		Operation getOperation();

		// 派生クラスに抽出するかも
		void developStrategy();
	protected:
		Operation operation;
		RobotData data[NUM_OF_ROBOT];
		ETeam owner[NUM_OF_POINT_OBJ];
	private:
		int Myid;
		EStrategy estr;
		Position target;
		Position POPos[NUM_OF_POINT_OBJ];
};
