#pragma once
#include <string>

class Map;
#include <list>
class Stage
{
public:
	Stage();
	~Stage();

	void Init();
	void DeInit();

	void Update(float deltaTime);
	void render();

	void pushStage(std::wstring mapName);


private:
	std::list<Map*> _mapList;

public:
	Map * GetMap();
};

