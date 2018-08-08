#pragma once
#include "Scene.h"

#include <list>



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
	Map * _map;

public:
	Map * GetMap() { return _map; }

};

