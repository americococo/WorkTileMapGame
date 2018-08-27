#include "PathMove_State.h"
#include "TileCell.h"
#include "SelfMoveObject.h"

#include "GameScene.h"
#include "SceneManager.h"
#include "Map.h"

PathMove_State::PathMove_State()
{
}

PathMove_State::~PathMove_State()
{
}

void PathMove_State::Start()
{
	State::Start();
	_movecheckTime = 0.0f;
	_pathTileCellStack = _moveObject->GetTileCellStack();
	_pathTileCellStack.pop();
}
void PathMove_State::Stop()
{
	State::Stop();
	_moveObject->ClearPathTileCellStack();
}
void PathMove_State::Update(float deltaTime)
{
	_movecheckTime += deltaTime;

	if (_movecheckTime < 0.3f)
		return;

	else
		_movecheckTime = 0.0f;


	if (0 != _pathTileCellStack.size())
	{
		TileCell* tileCell = _pathTileCellStack.top();
		_pathTileCellStack.pop();

		Position to;
		to.x = tileCell->GetTileX();
		to.y = tileCell->GetTileY();

		Position from;
		from.x = _moveObject->GetTileX();
		from.y = _moveObject->GetTileY();

		eDirection direction = GetDirection(to, from);

		if (eDirection::DIRCTION_NONE != direction)
			_moveObject->SetDirection(direction);

		std::list<Component*> componentList;

		bool canMove = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap()->GetTileCell(to)->GetCollisionList(componentList);

		if (true == canMove)
		{
			_moveObject->Moving(to);
			_moveObject->DecressActivePoint(1);
		}

		else
		{
			_nextState = eState::STATE_IDLE;
		}
	}
		
	if (false == _moveObject->IsActive())
		_nextState = eState::STATE_IDLE;

	State::Update(deltaTime);
}
void PathMove_State::render()
{
	State::render();
}
void PathMove_State::DeInit()
{
	State::DeInit();
}