#include "SelfMoveObject.h"

#include "Sprite.h"

#include "SceneManager.h"
#include "GameScene.h"
#include "Map.h"
#include "TileCell.h"

#include "State.h"
#include "IDLE_State.h"
#include "MOVE_State.h"
#include "GameSystem.h"

SelfMoveObject::SelfMoveObject(std::wstring name):Component(name)
{
	_state = nullptr;
}


SelfMoveObject::~SelfMoveObject()
{
	
}
void SelfMoveObject::Init()
{
	Map * map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();

	

	_currentDirection = eDirection::DIRCTION_DOWN;

	{
		State * state = new IDLE_State();
		state->Init(this);
		_stateDirection[eState::STATE_IDLE] = state;
	}

	{
		State * state = new MOVE_State();
		state->Init(this);
		_stateDirection[eState::STATE_MOVE] = state;
	}


	changeState(eState::STATE_IDLE);

	TileCell * tileCell = map->GetTileCell(1, 1);
	tileCell->AddComponent(this);
}

void SelfMoveObject::changeState(eState statetype)
{
	if (nullptr != _state)
	{
		_state->Stop();
		_state = nullptr;
	}

	_state = _stateDirection[statetype];
	_state->Start();
}

void SelfMoveObject::Update(float deltaTime)
{
	_state->Update(deltaTime);
}
void SelfMoveObject::SetPosition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;
}

void SelfMoveObject::render()
{
	_state->render();
}
void SelfMoveObject::DeInit()
{
	_state->DeInit();
}
void SelfMoveObject::UpdateMove()
{
	eDirection direction=eDirection::DIRCTION_NONE;

	if (GameSystem::GetInstance()->IsKeyDown(VK_LEFT))
		direction = eDirection::DIRCTION_LEFT;
	if (GameSystem::GetInstance()->IsKeyDown(VK_RIGHT))
		direction = eDirection::DIRCTION_RIGHT;
	if (GameSystem::GetInstance()->IsKeyDown(VK_UP))
		direction = eDirection::DIRCTION_UP;
	if (GameSystem::GetInstance()->IsKeyDown(VK_DOWN))
		direction = eDirection::DIRCTION_DOWN;


	if (eDirection::DIRCTION_NONE != direction)
	{
		_currentDirection = direction;
		_state->NextState(eState::STATE_MOVE);
	}

}