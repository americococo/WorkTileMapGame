#include "Monster.h"


#include "State.h"

Monster::Monster(std::wstring name):SelfMoveObject(name)
{
}


Monster::~Monster()
{
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
