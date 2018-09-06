#include "MOVE_State.h"

#include "SelfMoveObject.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Map.h"

#include "GameSystem.h"
#include "TileCell.h"
#include "Position.h"

#include "MessagePost.h"
#include "MessageFrom.h"
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


	GameScene * gmScene = ((GameScene*)SceneManager::GetInstance()->GetScene());




	if (false == gmScene->GetMap()->CanMove(currenPos,_moveObject->GetLayer()))
	{
		if (currenPos.x < 0 || currenPos.y < 0 || gmScene->GetMap()->GetWidth() <= currenPos.x || gmScene->GetMap()->GetHeight() <= currenPos.y)//예외처리 오브젝트가 맵밖으로 나가지지않기위함
			return;

		TileCell * tilecell = gmScene->GetMap()->GetTileCell(currenPos);
		
		if (nullptr!= tilecell && eObjectType::OBJECT_TYPE_ITEM == tilecell->GetTileObject(_moveObject->GetLayer())->GetObjectType())
		{
			MessageFrom messagefrom;
			messagefrom.message = L"UseItem";
			messagefrom.sender = _moveObject;
			messagefrom.reciver = (Object*)gmScene->GetMap()->GetTileCell(currenPos)->GetTileObject(eTileLayer::TileLayer_MIDLLE);
			gmScene->GetMap()->AddMessage(messagefrom);
		}

		if (nullptr != tilecell && _moveObject->GetEnemy() == tilecell->GetTileObject(_moveObject->GetLayer())->GetObjectType())
		{

			_moveObject->SetTarget(tilecell->GetTileObject(_moveObject->GetLayer()));
			_nextState = eState::STATE_ATTACK;

		}

		else
		{
			_nextState = eState::STATE_IDLE;
		}
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