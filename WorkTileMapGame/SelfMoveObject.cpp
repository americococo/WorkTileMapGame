#include "SelfMoveObject.h"

#include "Sprite.h"

#include "SceneManager.h"
#include "GameScene.h"
#include "Map.h"
#include "TileCell.h"
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

	_sprite = new Sprite(L"./Sprite/player/player.png",L"./Sprite/player/Up.json");
	_sprite->Init();
}
void SelfMoveObject::Update(float deltaTime)
{
	_sprite->Update(deltaTime);
}
void SelfMoveObject::SetPosition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;
}

void SelfMoveObject::render()
{
	_sprite->setPostition(_posX, _posY);
	_sprite->render();
}
void SelfMoveObject::DeInit()
{
	_sprite->deInit();
}