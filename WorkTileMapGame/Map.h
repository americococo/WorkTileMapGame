#pragma once
#include "Component.h"

#include <list>
#include <vector>
#include "Position.h"

class Sprite;
class TileCell;
class TileObject;
enum eTileLayer;
class SelfMoveObject;
class MessagePost;
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
	void CreateMap();//맵생성
	void CreateMap_layer_Ground();
	void CreateMap_layer(eTileLayer layer);
	void Create_Component();

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


	void removeComponent(Position tileposition, TileObject * tileobjet);
	void destroyComponent(Position tileposition, TileObject * tileobjet);

	void setTileComponent(Position tilePos, TileObject * tileobjet);


	bool CanMove(Position tilePosition,eTileLayer layer);
	void destroythisLayerComponent(eTileLayer tileLayer);

	//Map 그리기 중심 맞추기 관련
private:
	TileObject * _viewer;
public:
	void initViewer(TileObject * viewer);

	//Turn 관련
private:
	std::list<SelfMoveObject*> _turnList;
	std::list<SelfMoveObject*>::iterator _turnCircle;


	void turnUpdate();

public:
	void PushTurnList(SelfMoveObject * objcet);


private:
	MessagePost * _messagepost;


public:
	void AddMessage(MessageFrom messagefrom);
};

