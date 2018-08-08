#pragma once
#include "Scene.h"
class Sprite;
class TitleScene :	public Scene
{

public:
	TitleScene();
	~TitleScene();


	void Init();
	void DeInit();

	void Update(float deltaTime);
	void render();

private:
	Sprite * _sprite;
};

