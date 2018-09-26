#include "GameScene.h"

#include "Component.h"
#include "stage.h"
#include "Map.h"
GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}
void GameScene::Init()
{
	_stage = new Stage();
	_stage->pushStage(L"Map1");

}
void GameScene::DeInit()
{
	_stage->DeInit();
}

Map * GameScene::GetMap()
{
	return _stage->GetMap();
}
void GameScene::Update(float deltaTime)
{
	_stage->Update(deltaTime);
}
void GameScene::render()
{
	_stage->render();
}