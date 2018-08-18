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

#include <reader.h>
#include "ResourceManager.h"

SelfMoveObject::SelfMoveObject(std::wstring name)
{
	_state = nullptr;
	_name = name;
	_wing = nullptr;
	_tileLayer = eTileLayer::TileLayer_MIDLLE;

}


SelfMoveObject::~SelfMoveObject()
{
	
}
void SelfMoveObject::Init(WCHAR * TableFileName, Position tilePosition)
{
	std::vector<std::string> ScriptList = ResourceManager::GetInstance()->LoadScript(TableFileName);

	for (int i = 0; i < ScriptList.size(); i++)
	{
		std::string record = ScriptList[i];

		//Sinfile.getline(inputBuffer, 100);

		Json::Value root;
		Json::Reader reader;

		bool isSuccess = reader.parse(record, root);
		if (isSuccess)
		{

			_maxActivePoint = root["ActivePoint"].asInt();
			_tileLayer = (eTileLayer)root["layer"].asInt();

		}
	}


	((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap()->PushTurnList(this);

	Map * map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();

	if (_tileLayer == eTileLayer::TileLayer_SKY)
	{
		_wing = new Sprite(L"./Sprite/wing/Sprite.png", L"./Sprite/wing/Sprite.json");
		_wing->Init();
		_wing->setPostition(_posX, _posY);
	}
	

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

	if (_wing != nullptr)
		_wing->Update(deltaTime);
}
void SelfMoveObject::SetPosition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;
	
}

void SelfMoveObject::render()
{
	_state->render();

	if (_wing != nullptr)
	{
		_wing->setPostition(_posX, _posY);
		_wing->render();
	}
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

void SelfMoveObject::Moving(Position movingPos)
{
	if (movingPos.x == _tilePosition.x && movingPos.y == _tilePosition.y)
		return;

	Map * map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();
	map->removeComponent(_tilePosition,this);

	_tilePosition = movingPos;
	map->setTileComponent(_tilePosition, this);
}
void SelfMoveObject::DecressActivePoint(int activePoint)
{
	_activePoint -= activePoint;
	if (_activePoint <= 0)
		_activePoint = 0;
}