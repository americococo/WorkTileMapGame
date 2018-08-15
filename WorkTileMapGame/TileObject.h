#pragma once
#include "Component.h"
#include <string>
#include "Position.h"

enum eTileLayer;
class Sprite;
class TileObject : public Component
{
public:
	TileObject() {}
	TileObject(std::wstring name, Sprite * sprite, Position tilePosition, eTileLayer tileLayer);
	~TileObject();



	void Init();
	void Update(float deltaTime);
	void render();
	void DeInit();

	void SetPosition(float posX,float posY);

	eTileLayer GetLayer() { return _tileLayer; }
private:
	Sprite * _sprite;



protected:
	

	eTileLayer _tileLayer;
};

