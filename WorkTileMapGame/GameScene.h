#pragma once
#include "Scene.h"


class Stage;
class Map;
class GameScene :	public Scene
{

public:
	GameScene();
	~GameScene();

	void Init();
	void DeInit();

	void Update(float deltaTime);
	void render();


private:
	Stage * _stage;

public:
	Map * GetMap();

};

