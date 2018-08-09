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
public:
	void removeComponent(TileObject * tileobject);
private:
	std::map<eTileLayer,TileObject*> _componentList;
public:
	void AddTileObject(TileObject * tileobject);

public:
	bool CanMove(eTileLayer layer);
};

