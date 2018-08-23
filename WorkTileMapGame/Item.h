#pragma once
#include "Object.h"

#include "Sprite.h"
#include <Windows.h>

class Item : public Object
{
public:
	Item(std::wstring name);
	~Item();

public:
	void Init(WCHAR * TableFileName, Position tilePosition);
	void Update(float deltaTime);
	void render();
	void DeInit();



private:
	Sprite * _sprite;


	int _effectPower;

public:
	void ReciverMessage(MessageFrom msgFrom);
};

