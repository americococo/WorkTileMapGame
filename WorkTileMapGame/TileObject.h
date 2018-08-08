#pragma once
#include "Component.h"
#include <string>

class Sprite;
class TileObject : public Component
{
public:
	TileObject(std::wstring name, Sprite * sprite, int tileX, int tileY);
	~TileObject();



	void Init();
	void Update(float deltaTime);
	void render();
	void DeInit();

	void setCanMove(bool ismoving) { _isMoving = ismoving; }

	bool CanMove() { return _isMoving; }


	void SetPosition(float posX,float posY);
private:
	Sprite * _sprite;

	int _tileX;
	int _tileY;

	bool _isMoving;
};

