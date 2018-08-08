#pragma once
#include <map>
class SelfMoveObject;
class Sprite;

enum eState
{
	STATE_IDLE,
	STATE_MOVE,
};

enum eDirection;

class State
{
public:
	State();
	~State();

	virtual	void Init(SelfMoveObject * moveObject);
	virtual	void Update(float deltaTime);
	virtual	void render();
	virtual	void DeInit();

private:
	std::map<eDirection,Sprite*> _spriteList;
	SelfMoveObject * _moveObject;
};
