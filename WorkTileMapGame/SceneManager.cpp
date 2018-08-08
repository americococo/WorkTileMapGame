#include "SceneManager.h"

#include "Scene.h"
#include "TitleScene.h"
#include "GameScene.h"

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}
SceneManager * SceneManager::_instance=nullptr;

SceneManager * SceneManager::GetInstance()
{
	if (_instance == nullptr)
		_instance = new SceneManager();
	return _instance;
}

void SceneManager::Init()
{
	_scene = nullptr;
	{
		Scene * scene = new TitleScene();
		_sceneDirection[eScene::SC_TITLE] = scene;
	}
	{
		Scene * scene = new GameScene();
		_sceneDirection[eScene::SC_GAME] = scene;
	}

}
void SceneManager::ChangeScene(eScene scenetype)
{
	if (_scene != nullptr)
	{
		_scene->DeInit();
		delete _scene;
	}

	_scene = _sceneDirection[scenetype];
	_scene->Init();
}
void SceneManager::Update(float deltaTime)
{
	_scene->Update(deltaTime);
}
void SceneManager::render()
{
	_scene->render();
}