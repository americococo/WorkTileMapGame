#pragma once
#include <string>
#include "Position.h"

enum eObjectType
{
	OBJECT_TYPE_NONE,
	OBJECT_TYPE_TILE,
	OBJECT_TYPE_PLAYER,
	OBJECT_TYPE_MONSTER,
	OBJECT_TYPE_ITEM,
};
#include "MessageFrom.h"
class Component
{
public:
	Component() {}
	Component(std::wstring name);
	~Component();


	virtual void Init()=0;
	virtual void Update(float deltaTime)=0;
	virtual void render()=0;
	virtual void DeInit()=0;

	virtual void SetPosition(float posX, float posY) {}

	float GetPositionX() { return _posX; }
	float GetPositionY() { return _posY; }


	std::wstring GetName() { return _name; }

protected:
	std::wstring _name;

	float _posX;
	float _posY;

	Position _tilePosition;

	eObjectType _objectType;
public:
	int GetTileX() { return _tilePosition.x; }
	int GetTileY() { return _tilePosition.y; }



	//¸Þ¼¼Áö

	virtual void ReciverMessage(MessageFrom msgFrom);

	eObjectType GetObjectType() { return _objectType; }
};

