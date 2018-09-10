#include "Monster.h"


#include "State.h"
#include "PathMove_State.h"
#include "PathFind_State.h"
#include "Attack_State.h"
#include "MOVE_State.h"

#include "IDLE_State_Monster.h"



#include "Map.h"
#include "GameScene.h"
#include "SceneManager.h"

#include <reader.h>
#include "ResourceManager.h"
Monster::Monster(std::wstring name):SelfMoveObject(name)
{
	_objectType = eObjectType::OBJECT_TYPE_MONSTER;
}


Monster::~Monster()
{
}


void Monster::Init(WCHAR * TableFileName,Position tilePosition)
{
	std::vector<std::string> ScriptList = ResourceManager::GetInstance()->LoadScript(TableFileName);

	for (int i = 0; i < ScriptList.size(); i++)
	{
		std::string record = ScriptList[i];

		Json::Value root;
		Json::Reader reader;

		bool isSuccess = reader.parse(record, root);
		if (isSuccess)
		{
			switch (i)
			{
			case 1:
				_maxActivePoint = root["ActivePoint"].asInt();
				_tileLayer = (eTileLayer)root["layer"].asInt();
				_serachRange = root["Range"].asInt();
				break;
			case 2:
				_levelInfo.Health_Point = root["Hp"].asInt();
				_levelInfo.Mana_Point = root["Mp"].asInt();

				_levelInfo.Attack_Point = root["AttackPoint"].asInt();
				_levelInfo.Deffence_Point = root["DeffencePoint"].asInt();
				break;

			}

		}
	}

	_levelInfo.Max_Health_Point = _levelInfo.Health_Point;
	_levelInfo.Max_Mana_Point = _levelInfo.Mana_Point;


	SelfMoveObject::Init(TableFileName, tilePosition);

	InitState();


	_enemyType = (eObjectType::OBJECT_TYPE_PLAYER);

}
void Monster::InitState()
{
	{
		State * state = new IDLE_State_Monster();
		state->Init(this);
		_stateDirection[eState::STATE_IDLE] = state;
	}
	{
		State * state = new PathFind_State();
		state->Init(this);
		_stateDirection[eState::STATE_PATH_FIND] = state;
	}
	{
		State * state = new MOVE_State();
		state->Init(this);
		_stateDirection[eState::STATE_MOVE] = state;
	}
	{
		State * state = new PathMove_State();
		state->Init(this);
		_stateDirection[eState::STATE_PATH_MOVE] = state;
	}
	{
		State * state = new Attack_State();
		state->Init(this);
		_stateDirection[eState::STATE_ATTACK] = state;
	}



	changeState(eState::STATE_IDLE);
}
void Monster::UpdateMove()
{
	eDirection direction = eDirection::DIRCTION_NONE;

	direction = (eDirection)(rand() % eDirection::DIRCTION_NONE);

	if (eDirection::DIRCTION_NONE != direction)
	{
		_currentDirection = direction;
		_state->NextState(eState::STATE_MOVE);
	}

}

