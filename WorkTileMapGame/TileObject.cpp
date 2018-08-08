#include "TileObject.h"
#include "Sprite.h"
TileObject::TileObject(std::wstring name, Sprite * sprite, int tileX, int tileY)
{
	_sprite = sprite;
	_tileX = tileX;
	_tileY = tileY;
}

TileObject::~TileObject()
{
}

void TileObject::Init()
{
	_sprite->Init();
}
void TileObject::SetPosition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;
}
void TileObject::Update(float deltaTime)
{
	_sprite->Update(deltaTime);
}
void TileObject::render()
{
	_sprite->setPostition(_posX, _posY);
	_sprite->render();
}
void TileObject::DeInit()
{
	_sprite->deInit();
}