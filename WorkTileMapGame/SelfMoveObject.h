#pragma once
#include "Object.h"
#include <map>
#include <string>


#include "Position.h"

#include "LevelInfo.h"

class Sprite;
class State;

enum eState;
enum eTileLayer;

enum eDirection
{
	DIRCTION_LEFT,
	DIRCTION_RIGHT,
	DIRCTION_UP,
	DIRCTION_DOWN,
	DIRCTION_NONE,
};




class SelfMoveObject : 	public Object
{
public:
	SelfMoveObject(std::wstring name);
	~SelfMoveObject();

	virtual void Init(WCHAR * TableFileName, Position tilePosition);
	virtual void Update(float deltaTime);
	void render();
	void DeInit();

	

protected:

	std::map<eState, State*> _stateDirection;
	State * _state;

	eDirection _currentDirection;


	Sprite * _wing;

public:
	void SetDirection(eDirection direction) { _currentDirection = direction; }
	void SetPosition(float posX, float posY);

public:
	void changeState(eState changestate);

public:
	eDirection GetDirection() { return _currentDirection; }

	virtual void UpdateMove();

	void Moving(Position movingPos);

protected:
	float _movingTime;
public:
	float GetMovingTime() { return _movingTime; }


protected:
	int _activePoint;
	int _maxActivePoint;
public:
	void DecressActivePoint(int activePoint);
	bool IsActive() { return (0  < _activePoint); }
	void InitActivePoint() { _activePoint = _maxActivePoint; }
	void ResetActivePoint() { _activePoint = 0; }


	void recovering(int recoveringPoint);

protected:
	sLevelInfo _levelInfo;

};
