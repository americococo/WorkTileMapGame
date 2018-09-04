#include "IDLE_State_Monster.h"
#include "SelfMoveObject.h"

#include "Position.h"
#include "Monster.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Map.h"
#include "TileCell.h"
IDLE_State_Monster::IDLE_State_Monster()
{
}

IDLE_State_Monster::~IDLE_State_Monster()
{
}

void IDLE_State_Monster::Start()
{
	IDLE_State::Start();
	Map * map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();
	_tileQueue.push(map->GetTileCell(_moveObject->GetTilePosition()));

	for (int y = 0; y < map->GetHeight(); y++)
	{
		for (int x = 0; x < map->GetWidth(); x++)
		{
			Position position;
			position.x = x;
			position.y = y;
			TileCell* tileCell = map->GetTileCell(position);
			tileCell->InitPathfinding();
		}
	}

	while (0 != _tileQueue.size())
	{
		TileCell* tileCell = _tileQueue.front();
		_tileQueue.pop();

		if (false == tileCell->IsPathFindingMark())
		{
			tileCell->PathFinded();
			float distanceFromStart;
			for (int direction = 0; direction < eDirection::DIRCTION_NONE; direction++)
			{
				Position currentTilePos;
				currentTilePos.x = tileCell->GetTileX();
				currentTilePos.y = tileCell->GetTileY();
				Position nextTilePos = GetNextTilePosition(currentTilePos, (eDirection)direction);

				Map* map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();
				TileCell* currentTileCell = map->GetTileCell(currentTilePos);
				TileCell* nextTileCell = map->GetTileCell(nextTilePos);

				if (false == nextTileCell->IsPathFindingMark())
				{
					distanceFromStart = currentTileCell->GetDistanceFromStart() + 1.0f;
					nextTileCell->SetDistanceFromStart(distanceFromStart);
					nextTileCell->SetPrevPathFindingCell(tileCell);
					_tileQueue.push(nextTileCell);
					_serchTile[(int)distanceFromStart].push_back(nextTileCell);

					if (distanceFromStart >= ((Monster*)_moveObject)->GetSearchRange())
						return;
				}
			}
			
		}
	}

}
void IDLE_State_Monster::Stop()
{
	IDLE_State::Stop();
	while (false==_tileQueue.empty())
	{
		_tileQueue.pop();
	}
	
}
void IDLE_State_Monster::Update(float deltaTime)
{

	for (int i = 0; i < _serchTile.size(); i++)
	{
		std::vector<TileCell*>::iterator itr;
		itr = _serchTile[i].begin();

		for (itr; itr != _serchTile[i].end(); itr++)
		{
			TileObject * object = (*itr)->GetTileObject(eTileLayer::TileLayer_MIDLLE);
			if (nullptr != object)
			{
				eObjectType objectType = (*itr)->GetTileObject(eTileLayer::TileLayer_MIDLLE)->GetObjectType();
				if (objectType == _moveObject->GetEnemy())
				{
					_moveObject->SetTarget((*itr));
					_nextState = eState::STATE_PATH_FIND;
					_serchTile.clear();
					return;
				}
			}
		}
	}


	if (eState::STATE_NONE == _nextState)
	{
		_moveObject->UpdateMove();
	}

	State::Update(deltaTime);
}