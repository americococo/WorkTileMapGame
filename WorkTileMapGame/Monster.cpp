#include "Monster.h"


#include "State.h"

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

	SelfMoveObject::InitState();

	_enemy = eObjectType::OBJECT_TYPE_PLAYER;
}
void Monster::UpdateMove()
{
	eDirection direction = eDirection::DIRCTION_NONE;

	direction = ((eDirection)(rand() % 4));


	if (eDirection::DIRCTION_NONE != direction)
	{
		_currentDirection = direction;
		_state->NextState(eState::STATE_MOVE);
	}

}
