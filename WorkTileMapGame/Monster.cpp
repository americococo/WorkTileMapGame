#include "Monster.h"


#include "State.h"
#include "PathMove_State.h"
#include "PathFind_State.h"
#include "Attack_State.h"
#include "IDLE_State.h"

#include "Map.h"
#include "GameScene.h"
#include "SceneManager.h"
Monster::Monster(std::wstring name):SelfMoveObject(name)
{
	_objectType = eObjectType::OBJECT_TYPE_MONSTER;
}


Monster::~Monster()
{
}


void Monster::Init(WCHAR * TableFileName,Position tilePosition)
{
	SelfMoveObject::Init(TableFileName, tilePosition);

	InitState();

	_enemy = eObjectType::OBJECT_TYPE_PLAYER;
}
void Monster::InitState()
{
	{
		State * state = new IDLE_State();
		state->Init(this);
		_stateDirection[eState::STATE_IDLE] = state;
	}
	{
		State * state = new PathFind_State();
		state->Init(this);
		_stateDirection[eState::STATE_PATH] = state;
	}

	{
		State * state = new PathMove_State();
		state->Init(this);
		_stateDirection[eState::STATE_MOVE] = state;
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
	if (IsActive())
	{
		_state->NextState(eState::STATE_PATH);
	}
}
