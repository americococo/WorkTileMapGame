#pragma once

#include <map>

class Scene;

enum eScene;

class SceneManager
{
private:
	SceneManager();
public:
	~SceneManager();

private:
	static SceneManager * _instance;

public:
	static SceneManager * GetInstance();


public:
	void Init();


	void Update(float deltaTime);
	void render();

	void ChangeScene(eScene scenetype);



private:
	Scene * _scene;
	std::map<eScene, Scene*> _sceneDirection;



public:
	Scene * GetScene() { return _scene; }
};

