#include "TileCell.h"
#include "TileObject.h"
TileCell::TileCell(Position tilePosition)
{
	_tilePosition = tilePosition;
}

TileCell::~TileCell()
{

}
void TileCell::Init()
{

}
void TileCell::DeInit()
{
	
	for (std::map<eTileLayer, TileObject*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		itr->second->DeInit();
	}
}

void TileCell::setPostition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;

	for (std::map<eTileLayer, TileObject*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		if (nullptr != itr->second)
			itr->second->SetPosition(posX, posY);
	}
}

void TileCell::AddTileObject(TileObject * tileobject)
{
	_componentList[tileobject->GetLayer()] = tileobject;
}

void TileCell::Update(float deltaTime)
{
	while (false == _removeList.empty())
	{
		_componentList[_removeList.front()->GetLayer()] = nullptr;
		_removeList.pop_front();
	}
	

	for (std::map<eTileLayer, TileObject*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		if (nullptr != itr->second)
			itr->second->Update(deltaTime);
	}
}
void TileCell::render()
{
	for (std::map<eTileLayer, TileObject*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		if (nullptr != itr->second)
			itr->second->render();
	}
}
void TileCell::removeComponent(TileObject * tileobject)
{
	_removeList.push_back(tileobject);

}
bool TileCell::CanMove(eTileLayer layer)
{
	if (nullptr != _componentList[layer])
		return false;
	return true;
}