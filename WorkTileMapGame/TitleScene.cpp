#include "TitleScene.h"
#include "Sprite.h"

#include "GameSystem.h"
#include "SceneManager.h"
TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	_sprite = new Sprite(L"./Sprite/BackGround/BackGround.jpg", L"./Sprite/BackGround/BackGround.json");
	_sprite->Init();
	_sprite->setPostition(GameSystem::GetInstance()->GetWidth() / 2, GameSystem::GetInstance()->GetHeight() / 2);
}
void TitleScene::DeInit()
{
	_sprite->deInit();
}
void TitleScene::Update(float deltaTime)
{
	_sprite->Update(deltaTime);

	if (GameSystem::GetInstance()->IsKeyDown(VK_SPACE))
	{
		SceneManager::GetInstance()->ChangeScene(eScene::SC_GAME);
	}
}
void TitleScene::render()
{
	_sprite->render();
}