#pragma once
#include <string>

class Component
{
public:
	Component() {}
	Component(std::wstring name);
	~Component();


	virtual void Init()=0;
	virtual void Update(float deltaTime)=0;
	virtual void render()=0;
	virtual void DeInit()=0;

	virtual void SetPosition(float posX, float posY) {}

	float GetPositionX() { return _posX; }
	float GetPositionY() { return _posY; }

protected:
	std::wstring _name;

	float _posX;
	float _posY;
private:

};

