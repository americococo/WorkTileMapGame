#include "Stage.h"
#include "Map.h"

#include "SceneManager.h"
#include "Scene.h"
Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Init()
{
	_mapList.clear();
}
void Stage::DeInit()
{
	while (false==_mapList.empty())
	{
		Map * map = _mapList.back();
		map->DeInit();
		_mapList.pop_back();
		delete map;
	}
}

void Stage::Update(float deltaTime)
{
	if (_mapList.size() == 0)
	{
		SceneManager::GetInstance()->ChangeScene(eScene::SC_TITLE);
		return;
	}
		
	_mapList.front()->Update(deltaTime);

	if(_mapList.front()->CanClear())
	{
		Map * map = _mapList.front();
		map->DeInit();
		delete map;
		_mapList.pop_front();
	}

}
void Stage::render()
{
	if (_mapList.size() == 0)
		return;
	_mapList.front()->render();
}

void Stage::pushStage(std::wstring mapName)
{
	Map * map = new Map(mapName);

	_mapList.push_back(map);

	map->Init();

}
Map * Stage::GetMap()
{
	return _mapList.front();
}