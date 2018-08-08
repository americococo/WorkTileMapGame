#pragma once
#include "Component.h"

class Sprite;

class SelfMoveObject : 	public Component
{
public:
	SelfMoveObject(std::wstring name);
	~SelfMoveObject();

	void Init();
	void Update(float deltaTime);
	void render();
	void DeInit();

	void SetPosition(float posX, float posY);
private:
	Sprite * _sprite;
};

