#pragma once
#include <list>
#include "Component.h"
#include "Position.h"

#include <map>
class TileObject;
enum eTileLayer
{
	TileLayer_GROUND,
	TileLayer_MIDLLE,
	TileLayer_SKY,
	TileLayer_OVER,
};

class TileCell : public Component
{
public:
	TileCell(Position tilePosition);
	~TileCell();


	void Init();
	void DeInit();
	void setPostition(float posX,float posY);

	void Update(float deltaTime);

	void render();

private:
	std::list<TileObject*> _removeList;
	std::list<TileObject*> _destroyList;
public:
	void removeComponent(TileObject * tileobject);
	void destroyComponent(TileObject * tileobject);//destory 는 매모리내에서 완전히 삭제
	void destroyLayer(eTileLayer tileLayer);
private:
	std::map<eTileLayer,TileObject*> _componentList;
public:
	void AddTileObject(TileObject * tileobject);
	TileObject * GetTileObject(eTileLayer layer) { return _componentList[layer]; }
	bool GetCollisionList(std::list<Component*>& collisionList);
public:
	bool CanMove(eTileLayer layer);


private:
	bool _isPathfindingMark;
	TileCell* _prePathfindingCell;

	float _distanceWeight;
	float _distanceFromStart;

	float _heuristic;


public:
	void InitPathfinding();
	bool IsPathFindingMark() { return _isPathfindingMark; }
	void PathFinded() { _isPathfindingMark = true; }
	int GetTileX() { return _tilePosition.x; }
	int GetTileY() { return _tilePosition.y; }

	TileCell* GetPrevPathFindingCell() { return _prePathfindingCell; }
	void SetPrevPathFindingCell(TileCell* tileCell) { _prePathfindingCell = tileCell; }
	float GetDistanceWeight() { return _distanceWeight; };
	float GetDistanceFromStart() { return _distanceFromStart; };
	void SetDistanceFromStart(float distance) { _distanceFromStart = distance; };

	float GetHeuristic() { return _heuristic; }
	void SetHeuristic(float heuristic) { _heuristic = heuristic; }
};

