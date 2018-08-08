#include "GameScene.h"

#include "Component.h"
#include "Map.h"
GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}
void GameScene::Init()
{
	_map = new Map(L"Map1");
	_map->Init();
}
void GameScene::DeInit()
{
	_map->DeInit();
}
void GameScene::Update(float deltaTime)
{
	_map->Update(deltaTime);
}
void GameScene::render()
{
	_map->render();
}