#include "Player.h"

#include "TileCell.h"
#include "IDLE_State.h"
#include "MOVE_State.h"

#include "GameScene.h"
#include "SceneManager.h"
#include "Map.h"

#include "GameSystem.h"

Player::Player(std::wstring name):SelfMoveObject(name)
{
	_objectType = eObjectType::OBJECT_TYPE_PLAYER;
}


Player::~Player()
{
}
void Player::Init(int activePoint, Position tilePosition, eTileLayer layer)
{
	_maxActivePoint = activePoint;

	_tileLayer = layer;


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

	_movingTime = 0.3f;

	_tilePosition = tilePosition;

}
void Player::UpdateMove()
{
	eDirection direction = eDirection::DIRCTION_NONE;

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