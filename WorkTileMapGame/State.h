#pragma once
#include <map>
class SelfMoveObject;
class Sprite;

enum eState
{
	STATE_IDLE,
	STATE_MOVE,
	STATE_ATTACK,
	STATE_SKILL,
	STATE_PATH,
	STATE_NONE,
	
};

enum eDirection;

class State
{
public:
	State();
	~State();

	void Init(SelfMoveObject * moveObject);
	virtual	void Start();
	virtual	void Stop();
	virtual	void Update(float deltaTime);
	virtual	void render();
	virtual	void DeInit();


	void NextState(eState stateType);
protected:
	std::map<eDirection,Sprite*> _spriteList;
	SelfMoveObject * _moveObject;

	eState _nextState;
};
