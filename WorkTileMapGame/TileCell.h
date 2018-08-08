#pragma once
#include <list>
#include "Component.h"
#include "Position.h"

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
	std::list<Component*> _removeList;
public:
	void removeComponent(Component * com);
private:
	std::list<Component*> _componentList;
public:
	void AddComponent(Component * com);
};

