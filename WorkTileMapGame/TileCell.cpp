#include "TileCell.h"

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
	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->DeInit();
	}
}

void TileCell::setPostition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;

	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->SetPosition(posX,posY);
	}
}

void TileCell::AddComponent(Component * com)
{
	_componentList.push_back(com);
}

void TileCell::Update(float deltaTime)
{
	while (false == _removeList.empty())
	{
		_componentList.remove(_removeList.front());
		_removeList.pop_front();
	}
	

	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->Update(deltaTime);
	}
}
void TileCell::render()
{
	for (std::list<Component*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		(*itr)->render();
	}
}
void TileCell::removeComponent(Component * com)
{
	_removeList.push_back(com);
}