#pragma once
#include "Component.h"

#include <list>
#include <vector>
#include "Position.h"
class Sprite;
class TileCell;

class Map : public Component
{
public:
	Map(std::wstring name);
	~Map();

	void Init();
	void Update(float deltaTime);
	void render();
	void DeInit();

private:
	void CreateMap();//¸Ê»ý¼º
	void CreateMap_layer1();
	void CreateMap_layer2();

private:
	int _width;
	int _height;
	int _tileSize;
	std::vector <Sprite*> _spriteList;

	std::vector < std::vector < TileCell*>> _tileMap;


	float _posX, _posY;
	float _startX, _startY;

public:
	int GetWidth() { return _width; }
	int GetHeight() { return _height; }
public:
	TileCell * GetTileCell(Position tileposition) { return _tileMap[tileposition.y][tileposition.x]; }


	void removeComponent(Position tileposition,Component * com);

	void setTileComponent(Position tilePos, Component* component);
};

