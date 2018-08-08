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

	void Init(SelfMoveObject * moveObject);
	void Update(float deltaTime);
	void render();
	void DeInit();
private:
	std::map<eDirection,Sprite*> _spriteList;
	SelfMoveObject * _moveObject;
};
