#include "SelfMoveObject.h"

#include "Sprite.h"

#include "SceneManager.h"
#include "GameScene.h"
#include "Map.h"
#include "TileCell.h"

#include "State.h"

SelfMoveObject::SelfMoveObject(std::wstring name):Component(name)
{

}


SelfMoveObject::~SelfMoveObject()
{
}
void SelfMoveObject::Init()
{
	Map * map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();

	TileCell * tileCell = map->GetTileCell(1, 1);
	tileCell->AddComponent(this);

	_currentDirection = eDirection::DIRCTION_DOWN;

	{
		State * state = new State();
		state->Init(this);
		_stateDirection[eState::STATE_IDLE] = state;
		_state = state;//test
	}
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