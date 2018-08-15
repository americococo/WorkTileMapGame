#include "MOVE_State.h"

#include "SelfMoveObject.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Map.h"

#include "GameSystem.h"

#include "Position.h"
MOVE_State::MOVE_State()
{
	
}


MOVE_State::~MOVE_State()
{
}
void MOVE_State::Start()
{
	State::Start();

	_movecheckTime = 0.0f;

	eDirection direction = _moveObject->GetDirection();

	Position currenPos;
	currenPos.x = _moveObject->GetTileX();
	currenPos.y = _moveObject->GetTileY();

	switch (direction)
	{
	case eDirection::DIRCTION_LEFT:
		currenPos.x--;
		break;
	case eDirection::DIRCTION_RIGHT:
		currenPos.x++;
		break;
	case eDirection::DIRCTION_UP:
		currenPos.y--;
		break;
	case eDirection::DIRCTION_DOWN:
		currenPos.y++;
		break;
	}
	if (currenPos.x < 0)
		currenPos.x = 0;
	if (currenPos.y < 0)
		currenPos.y = 0;

	GameScene * gmScene = ((GameScene*)SceneManager::GetInstance()->GetScene());

	if (gmScene->GetMap()->GetWidth() <= currenPos.x)
		currenPos.x = currenPos.x - 1;
	if (gmScene->GetMap()->GetHeight() <= currenPos.y)
		currenPos.y= currenPos.y - 1;


	if (false == gmScene->GetMap()->CanMove(currenPos,_moveObject->GetLayer()))
	{
		_nextState = eState::STATE_IDLE;
	}
	else
	{
		_moveObject->DecressActivePoint(1);
		_moveObject->Moving(currenPos);
	}
}
void MOVE_State::Stop()
{
	State::Stop();
}
void MOVE_State::Update(float deltaTime)
{
	_movecheckTime += deltaTime;

	if (_movecheckTime >= _moveObject->GetMovingTime())
	{
		_nextState = eState::STATE_IDLE;
		_movecheckTime = 0.0f;
	}


	State::Update(deltaTime);
}
void MOVE_State::render()
{
	State::render();
}
void MOVE_State::DeInit()
{
	State::DeInit();
}