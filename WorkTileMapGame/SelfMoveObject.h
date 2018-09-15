#pragma once
#include "Object.h"
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <stack>
#include <list>
#include "Position.h"

#include "LevelInfo.h"
#include "MessageFrom.h"



class Sprite;
class State;
class TileCell;


enum eState;
enum eTileLayer;
enum SkillType;
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
	virtual void InitState();
public:
	eDirection GetDirection() { return _currentDirection; }

	virtual void UpdateMove();

	void Moving(Position movingPos);
	Component * Colision(std::list<Component*>& colisionList);
protected:
	float _movingTime;
public:
	float GetMovingTime() { return _movingTime; }



public:
	void DecressActivePoint(int activePoint);
	bool IsActive() { return (0  < _activePoint); }
	void InitActivePoint() { _activePoint = _maxActivePoint; }
	void ResetActivePoint() { _activePoint = 0; }


	void recoveringHp(int recoveringPoint);
	void DecressingHp(int DecressingPoint);
	void ReciverMessage(MessageFrom msgFrom);


protected:
	eObjectType _enemyType;

public:
	eObjectType GetEnemy() { return _enemyType; }


protected:
	Component * _target;

public:
	void SetTarget(Component * target) { _target = target; }

	Component * GetTarget() { return _target; }
	void ResetTarget() { _target = nullptr; }
public:
	sLevelInfo GetStatus() { return _levelInfo; }


protected:
	SkillType _skillType;
	
public:
	void SetSkillType(SkillType skilltype) { _skillType = skilltype; }
	SkillType GetSkillType() { return _skillType; }


	void StartSkill();
	void UpdateSkill(float deltaTime);

private:
	int _currentWave;

	std::queue <TileCell *>  _RangeAttackQueue;

	std::map<int,std::vector<TileCell*>> _waveTileCellList;


	void AttackEffectWave(int waveIndex);


	float _waveCheckingTime;


private:
	std::stack<TileCell*> _pathTileCellStack;

public:
	std::stack<TileCell*> GetTileCellStack() { return _pathTileCellStack; }
	void PushTileCell(TileCell* tileCell) { _pathTileCellStack.push(tileCell); }


	void ClearPathTileCellStack();
};
