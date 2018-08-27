#pragma once
#include "State.h"

#include <queue>

class TileCell;

class PathFind_State :public State
{
public:
	PathFind_State();
	~PathFind_State();


	void Start();
	void Stop();
	void Update(float deltaTime);
	void render();
	void DeInit();

public:
	enum eUpdateState
	{
		PATHFINDING,
		BUILD_PATH
	};

	typedef struct _sPathCommand
	{
		float heuristic;
		TileCell * tilecell;
	}sPathCommand;

	//pathFinding
	struct  compare
	{
		bool operator()(sPathCommand&  a, sPathCommand&  b)
		{
			//return a->getDistanceFromStart() > b->getDistanceFromStart();
			return a.heuristic < b.heuristic;
		}
	};


protected:
	//std::queue<tileCell*> _pathfingTileQueue;
	std::priority_queue<sPathCommand, std::vector<sPathCommand>, compare> _pathfingTileQueue;
	TileCell * _targetTileCell;

	eUpdateState _updateState;

protected:
	TileCell * _reverseTilecell;

public:
	void UpdatePathfinding();
	void UpdateBuildPath();



	float CalcSimpleHeuristic(TileCell* tilecell, TileCell* nextTileCell, TileCell* _targetTileCell);//방향만 검사 현재 타일에서 목적지까지 방향
	float CalcComplectHeuristic(TileCell * nextTilecell, TileCell * targetTileCell); //목적지까지 거리
	float CalcAStarHeuristic(float distanceFromStart, TileCell * nextTilecell, TileCell * targetTileCell);

};

