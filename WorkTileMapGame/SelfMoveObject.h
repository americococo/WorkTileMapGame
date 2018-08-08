#pragma once
#include "Component.h"
#include <map>
#include <string>


#include "Position.h"
class Sprite;
enum eState;
class State;

enum eDirection
{
	DIRCTION_LEFT,
	DIRCTION_RIGHT,
	DIRCTION_UP,
	DIRCTION_DOWN,
	DIRCTION_NONE,
};

class SelfMoveObject : 	public Component
{
public:
	SelfMoveObject(std::wstring name);
	~SelfMoveObject();

	void Init();
	void Update(float deltaTime);
	void render();
	void DeInit();

	

private:

	std::map<eState, State*> _stateDirection;
	State * _state;

	eDirection _currentDirection;

public:
	void SetDirection(eDirection direction) { _currentDirection = direction; }
	void SetPosition(float posX, float posY);

public:
	void changeState(eState changestate);

public:
	eDirection GetDirection() { return _currentDirection; }

	void UpdateMove();

	void Moving(Position movingPos);

private:
	float _movingTime;
public:
	float GetMovingTime() { return _movingTime; }

};

