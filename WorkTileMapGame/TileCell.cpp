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
	InitPathfinding();
}
void TileCell::DeInit()
{
	
	for (std::map<eTileLayer, TileObject*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		if (itr->second != nullptr)
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
	while (0!=_removeList.size())
	{
		_componentList[_removeList.front()->GetLayer()] = nullptr;
		_removeList.pop_front();
	}

	while (0!=_destroyList.size())
	{
		 TileObject * object= _destroyList.front();
		_componentList[_destroyList.front()->GetLayer()] = nullptr;
		_destroyList.pop_front();

		delete object;
	}


	for (std::map<eTileLayer, TileObject*>::iterator itr = _componentList.begin(); itr != _componentList.end(); itr++)
	{
		if (nullptr != itr->second)
			itr->second->Update(deltaTime);
	}
}
bool TileCell::GetCollision(Component*& collision,eTileLayer layer)
{
	if (nullptr == _componentList[layer])
	{
		
		return true;
	}
	else 
	{
		collision = _componentList[layer];
		return false;
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
void TileCell::destroyComponent(TileObject * tileobject)
{
	_destroyList.push_back(tileobject);
}

void TileCell::destroyLayer(eTileLayer tileLayer)
{
	if (_componentList[tileLayer] != nullptr)
		_destroyList.push_back(_componentList[tileLayer]);
}
bool TileCell::CanMove(eTileLayer layer)
{
	if (nullptr != _componentList[layer])
		return false;
	return true;
}
void TileCell::InitPathfinding()
{
	_isPathfindingMark = false;
	_prePathfindingCell = nullptr;
	_distanceFromStart = 0.0f;
	_heuristic = 0.0f;
}