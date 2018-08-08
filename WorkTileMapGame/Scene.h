#pragma once

enum eScene
{
	SC_TITLE,
	SC_GAME,
	SC_OVER,
};

class Scene
{
public:
	Scene();
	~Scene();


	virtual void Init();
	virtual void DeInit();

	virtual void Update(float deltaTime);
	virtual void render();
};

