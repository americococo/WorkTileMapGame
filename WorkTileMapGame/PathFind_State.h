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



	float CalcSimpleHeuristic(TileCell* tilecell, TileCell* nextTileCell, TileCell* _targetTileCell);//���⸸ �˻� ���� Ÿ�Ͽ��� ���������� ����
	float CalcComplectHeuristic(TileCell * nextTilecell, TileCell * targetTileCell); //���������� �Ÿ�
	float CalcAStarHeuristic(float distanceFromStart, TileCell * nextTilecell, TileCell * targetTileCell);

};

