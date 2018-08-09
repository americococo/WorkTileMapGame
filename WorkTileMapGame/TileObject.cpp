#include "TileObject.h"
#include "Sprite.h"
TileObject::TileObject(std::wstring name, Sprite * sprite, Position tilePosition, eTileLayer tileLayer)
{
	_sprite = sprite;
	_tilePosition = tilePosition;
	_tileLayer = tileLayer;
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