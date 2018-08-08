#pragma once
#include <list>
#include "Component.h"
class TileCell : public Component
{
public:
	TileCell(int tileX,int tileY);
	~TileCell();


	void Init();
	void DeInit();
	void setPostition(float posX,float posY);

	void AddComponent(Component * com);
	void Update(float deltaTime);

	void render();
private:
	int _tileX;
	int _tileY;

	std::list<Component*> _componentList;
};

