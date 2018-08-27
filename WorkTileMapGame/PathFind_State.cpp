#include "PathFind_State.h"
#include "SelfMoveObject.h"
#include "TileCell.h"
#include "Position.h"

#include "Map.h"
#include "GameScene.h"
#include "SceneManager.h"

#include "Sprite.h"

PathFind_State::PathFind_State()
{
}

PathFind_State::~PathFind_State()
{
}
void PathFind_State::Start()
{
	State::Start();
	Map* map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();
	_moveObject->SetTarget((Component*)map->GetPlayer());

	_targetTileCell = map->GetTileCell(_moveObject->GetTarget()->GetTilePosition());

	// ���Ÿ�ϼ��� ��ã�� �Ӽ� �ʱ�ȭ
	int height = map->GetHeight();
	int width = map->GetWidth();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Position position;
			position.x = x;
			position.y = y;
			TileCell* tileCell = map->GetTileCell(position);
			tileCell->InitPathfinding();
		}
	}

	TileCell* startTileCell = map->GetTileCell(_moveObject->GetTilePosition());
	sPathCommand newCommand;
	newCommand.heuristic = 0.0f;
	newCommand.tilecell = startTileCell;
	_pathfingTileQueue.push(newCommand);

	_updateState = eUpdateState::PATHFINDING;
}
void PathFind_State::Stop()
{
	State::Stop();
	
	while (0 != _pathfingTileQueue.size())
	{
		_pathfingTileQueue.pop();
	}
}
float PathFind_State::CalcSimpleHeuristic(TileCell* tileCell, TileCell* nextTileCell, TileCell* targetTileCell)
{
	float heuristic = 0.0f;

	int diffFromCurrent = 0;
	int diffFromNext = 0;

	//x : �߰��� ���� ����
	{
		diffFromCurrent = tileCell->GetTileX() - targetTileCell->GetTileX();
		if (diffFromCurrent < 0)
			diffFromCurrent = -diffFromCurrent;

		diffFromNext = nextTileCell->GetTileX() - targetTileCell->GetTileX();
		if (diffFromNext < 0)
			diffFromNext = -diffFromNext;

		if (diffFromNext < diffFromCurrent)
		{
			heuristic -= 1.0f;
		}
		else if (diffFromNext > diffFromCurrent)
		{
			heuristic += 1.0f;
		}
	}

	//y : �߰��� ���� ���� ����
	{
		diffFromCurrent = tileCell->GetTileY() - targetTileCell->GetTileY();
		if (diffFromCurrent < 0)
			diffFromCurrent = -diffFromCurrent;

		diffFromNext = nextTileCell->GetTileY() - targetTileCell->GetTileY();
		if (diffFromNext < 0)
			diffFromNext = -diffFromNext;


		if (diffFromNext < diffFromCurrent)
		{
			heuristic -= 1.0f;
		}
		else if (diffFromNext > diffFromCurrent)
		{
			heuristic += 1.0f;
		}
	}

	return heuristic;
}

float PathFind_State::CalcComplectHeuristic(TileCell* nextTileCell, TileCell* targetTileCell)
{
	int distanceW = nextTileCell->GetTileX() - targetTileCell->GetTileX();
	int distanceH = nextTileCell->GetTileY() - targetTileCell->GetTileY();

	distanceW = distanceW * distanceW;
	distanceH = distanceH * distanceH;

	float distance = (float)((double)distanceW + (double)distanceH);
	return distance;
}

float PathFind_State::CalcAStarHeuristic(float distanceFromStart, TileCell* nextTileCell, TileCell* targetTileCell)
{
	return distanceFromStart + CalcComplectHeuristic(nextTileCell, targetTileCell);
}

void PathFind_State::Update(float deltaTime)
{
	switch (_updateState)
	{
	case eUpdateState::PATHFINDING:
		UpdatePathfinding(); break;
	case eUpdateState::BUILD_PATH:
		UpdateBuildPath(); break;
	}

	State::Update(deltaTime);
}
void PathFind_State::UpdatePathfinding()
{
	if (0 != _pathfingTileQueue.size())
	{
		//ť�� ó�� ���� �� �˻�
		//tileCell * tilecell = _pathfingTileQueue.top();
		sPathCommand command = _pathfingTileQueue.top();
		_pathfingTileQueue.pop();

		if (false == command.tilecell->IsPathFindingMark())
		{
			command.tilecell->PathFinded();

			//��ǥŸ�� -> ����
			if (command.tilecell->GetTileX() == _targetTileCell->GetTileX() && command.tilecell->GetTileY() == _targetTileCell->GetTileY())
			{
				std::list<Component*> comList;
				command.tilecell->GetCollisionList(comList);

				for (std::list<Component*>::iterator itr = comList.begin(); itr != comList.end(); itr++)
				{

					if (_moveObject->GetEnemy() == (*itr)->GetObjectType())
					{
						SelfMoveObject * enemy = (SelfMoveObject*)(*itr);
						TileCell * prev = command.tilecell->GetPrevPathFindingCell();

						if (command.tilecell->GetTileX() < prev->GetTileX())
							_moveObject->SetDirection(eDirection::DIRCTION_RIGHT);
						else if (prev->GetTileX() <command.tilecell->GetTileX())
							_moveObject->SetDirection(eDirection::DIRCTION_LEFT);
						else if (prev->GetTileY() < command.tilecell->GetTileY())
							_moveObject->SetDirection(eDirection::DIRCTION_UP);
						else if (command.tilecell->GetTileY() < prev->GetTileY())
							_moveObject->SetDirection(eDirection::DIRCTION_DOWN);
					}
				}

				_updateState = eUpdateState::BUILD_PATH;
				_reverseTilecell = _targetTileCell;
				return;
			}
			for (int direction = 0; direction < eDirection::DIRCTION_NONE; direction++)
			{
				Position currentTilePos;
				currentTilePos.x = command.tilecell->GetTileX();
				currentTilePos.y = command.tilecell->GetTileY();
				Position nextTilePos = GetNextTilePosition(currentTilePos, (eDirection)direction);

				Map * map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();
				TileCell * nextTileCell = map->GetTileCell(nextTilePos);

				//��ֹ� üũ Ž���� ������ üũ
				if ((true == map->CanMove(nextTilePos,_moveObject->GetLayer()) && false == nextTileCell->IsPathFindingMark()) ||
					(nextTileCell->GetTileX() == _targetTileCell->GetTileX() && nextTileCell->GetTileY() == _targetTileCell->GetTileY()))
				{
					float distanceFromStart = command.tilecell->GetDistanceFromStart() + command.tilecell->GetDistanceWeight();

					//float heuristic = CalcSimpleHeyristic(tilecell,nextTileCell,_targetTileCell);
					//float heuristic = CalcComplexcHeuristic(nextTileCell, _targetTileCell);
					float heuristic = CalcAStarHeuristic(distanceFromStart, nextTileCell, _targetTileCell);

					if (NULL == nextTileCell->GetPrevPathFindingCell())
					{
						//�Ÿ��켱 Ž�� - �ִܰŸ� d ��� Ÿ�� Ž��
						nextTileCell->SetDistanceFromStart(distanceFromStart);

						//�߰��� Ž�� - ���������� �Ÿ� Ž�� d ������������ (����� �Ÿ�) �߿�� x
						nextTileCell->SetHeuristic(heuristic);

						//Ž���� ��ε��� �Ÿ� ��

						nextTileCell->SetPrevPathFindingCell(command.tilecell);

						sPathCommand newCommand;
						newCommand.heuristic = heuristic;
						newCommand.tilecell = nextTileCell;
						_pathfingTileQueue.push(newCommand);

					}

					else
					{
						if (distanceFromStart < nextTileCell->GetDistanceFromStart())
						{
							//�ٽð˻�
							nextTileCell->SetDistanceFromStart(distanceFromStart);
							nextTileCell->SetPrevPathFindingCell(command.tilecell);

							sPathCommand newCommand;
							newCommand.heuristic = CalcAStarHeuristic(distanceFromStart, nextTileCell, _targetTileCell);
							newCommand.tilecell = nextTileCell;
							_pathfingTileQueue.push(newCommand);
						}
					}
				}
			}
		}

	}
	else
	{
		_moveObject->DecressActivePoint(_moveObject->GetMaxActivePoint());
		_nextState = eState::STATE_IDLE;
	}

}
void PathFind_State::UpdateBuildPath()
{
	if (NULL != _reverseTilecell)
	{
		Sprite * sprite = new Sprite(L"./Sprite/Attack/wave.png", L"./Sprite/Attack/wave.json");
		sprite->Init();
		TileObject * object;
		object = new TileObject(L"", sprite, _reverseTilecell->GetTilePosition(), eTileLayer::TileLayer_OVER);
		object->Init();

		Map* map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();
		map->GetTileCell(_reverseTilecell->GetTilePosition())->AddTileObject(object);

		_moveObject->PushTileCell(_reverseTilecell);
		_reverseTilecell = _reverseTilecell->GetPrevPathFindingCell();
	}
	else
	{
		_nextState = eState::STATE_MOVE;
	}

}

void PathFind_State::render()
{
	State::render();
}
void PathFind_State::DeInit()
{
	State::DeInit();
}