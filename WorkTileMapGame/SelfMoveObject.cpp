#include "SelfMoveObject.h"

#include "Sprite.h"

#include "SceneManager.h"
#include "GameScene.h"
#include "Map.h"
#include "TileCell.h"

#include "State.h"
#include "IDLE_State.h"
#include "MOVE_State.h"
#include "Attack_State.h"
#include "Skill_State.h"


#include "GameSystem.h"

#include <reader.h>
#include "ResourceManager.h"

SelfMoveObject::SelfMoveObject(std::wstring name):Object(name)
{
	_state = nullptr;
	_wing = nullptr;
	_tileLayer = eTileLayer::TileLayer_MIDLLE;



	_target = nullptr;
}


SelfMoveObject::~SelfMoveObject()
{
	
}
void SelfMoveObject::Init(WCHAR * TableFileName, Position tilePosition)
{

	((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap()->PushTurnList(this);

	Map * map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();

	if (_tileLayer == eTileLayer::TileLayer_SKY)
	{
		_wing = new Sprite(L"./Sprite/wing/Sprite.png", L"./Sprite/wing/Sprite.json");
		_wing->Init();
		_wing->setPostition(_posX, _posY);
	}
	

	_currentDirection = eDirection::DIRCTION_DOWN;

	_movingTime = 0.3f;

	_tilePosition = tilePosition;


}
void SelfMoveObject::InitState()
{

	{
		State * state = new IDLE_State();
		state->Init(this);
		_stateDirection[eState::STATE_IDLE] = state;
	}

	{
		State * state = new MOVE_State();
		state->Init(this);
		_stateDirection[eState::STATE_MOVE] = state;
	}
	{
		State * state = new Attack_State();
		state->Init(this);
		_stateDirection[eState::STATE_ATTACK] = state;
	}

	changeState(eState::STATE_IDLE);
}

void SelfMoveObject::changeState(eState statetype)
{
	if (nullptr != _state)
	{
		_state->Stop();
		_state = nullptr;
	}

	_state = _stateDirection[statetype];
	_state->Start();
}

void SelfMoveObject::Update(float deltaTime)
{
	if (_activePoint <= 0)
		return;

	_state->Update(deltaTime);


	if (_wing != nullptr)
		_wing->Update(deltaTime);
}

void SelfMoveObject::SetPosition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;
	
}

void SelfMoveObject::render()
{
	_state->render();
	

	if (_wing != nullptr)
	{
		_wing->setPostition(_posX, _posY);
		_wing->render();
	}


}
void SelfMoveObject::DeInit()
{
	_state->DeInit();
}
void SelfMoveObject::UpdateMove()
{

}
Component * SelfMoveObject::Colision(std::list<Component*>& colisionList)
{
	for (std::list<Component*>::iterator itr = colisionList.begin(); itr != colisionList.end(); itr++)
	{
		Component * com = (*itr);
		if (com->GetObjectType() == _enemy)
		{
			return  (*itr);
		}
	}
	return nullptr;
}
void SelfMoveObject::Moving(Position movingPos)
{
	if (movingPos.x == _tilePosition.x && movingPos.y == _tilePosition.y)
		return;

	Map * map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();
	map->removeComponent(_tilePosition,this);

	_tilePosition = movingPos;
	map->setTileComponent(_tilePosition, this);
}
void SelfMoveObject::recoveringHp(int recoveringPoint)
{
	_levelInfo.Health_Point += recoveringPoint;
	if (_levelInfo.Health_Point >= _levelInfo.Max_Health_Point)
		_levelInfo.Health_Point = _levelInfo.Max_Health_Point;
}
void SelfMoveObject::DecressingHp(int DecressingPoint)
{
	_levelInfo.Health_Point -= DecressingPoint;
	if (_levelInfo.Health_Point <= 0)
	{
		_levelInfo.Health_Point = 0;
		Map * map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();
		map->GetTileCell(_tilePosition)->destroyComponent(this);
	}
}

void SelfMoveObject::ReciverMessage(MessageFrom msgFrom)
{
	if (L"Attack" == msgFrom.message)
	{
		sLevelInfo stat = ((SelfMoveObject*)msgFrom.sender)->GetStatus();

		int damage;
		float deffenceRate = 0.01 * (100 - _levelInfo.Deffence_Point);

		damage=(float)(stat.Attack_Point) *  deffenceRate;

		DecressingHp(damage);
	}
}

void SelfMoveObject::DecressActivePoint(int activePoint)
{
	_activePoint -= activePoint;
	if (_activePoint <= 0)
	{
		_activePoint = 0;
		_state->NextState(eState::STATE_IDLE);
	}
}

void SelfMoveObject::StartSkill()
{
	Map * map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();


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
	_currentWave = 0;
	_waveTileCellList.clear();
	_waveCheckingTime = 0.0f;
	switch (_skillType)
	{
	case SKILLTYPE_RANGEATTACK:
		_RangeAttackQueue.push(map->GetTileCell(_tilePosition));


		while (0 != _RangeAttackQueue.size())
		{
			TileCell* tileCell = _RangeAttackQueue.front();
			_RangeAttackQueue.pop();

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
						if (_activePoint == (int)distanceFromStart)
							break;
						nextTileCell->SetDistanceFromStart(distanceFromStart);
						nextTileCell->SetPrevPathFindingCell(tileCell);
						_RangeAttackQueue.push(nextTileCell);
						_waveTileCellList[(int)distanceFromStart].push_back(nextTileCell);
					}
				}
			}
		}

	}

}
void SelfMoveObject::AttackEffectWave(int waveIndex)
{
	if (waveIndex == _activePoint)
		return;
	int i = 0;
	for (std::vector<TileCell*>::iterator itr = _waveTileCellList[waveIndex].begin(); itr != _waveTileCellList[waveIndex].end(); itr++)
	{

		Component * com=nullptr;
		(*itr)->GetCollision(com,_tileLayer);

		i++;
		Sprite* sprite = new Sprite(L"./Sprite/Attack/Wave.png", L"./Sprite/Attack/Wave.json");
		sprite->Init();

		WCHAR componetName[256];
		wsprintf(componetName, L"Wave_%d_%d", waveIndex, i);

		Position position;
		position.x = (*itr)->GetPositionX();
		position.y = (*itr)->GetPositionY();
		TileObject * tileObject = new TileObject(componetName, sprite, position, eTileLayer::TileLayer_OVER);
		tileObject->Init();

		(*itr)->AddTileObject(tileObject);

		SelfMoveObject * move = (SelfMoveObject*)com;
		MessageFrom msgParam;
		msgParam.sender = this;
		msgParam.reciver = move;
		msgParam.message = L"Attack";
		Map* map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();
		map->AddMessage(msgParam);

	}
}
void SelfMoveObject::UpdateSkill(float deltaTime)
{
	_waveCheckingTime += deltaTime;
	
	AttackEffectWave(_currentWave);
	_currentWave++;

	if (_currentWave >= _activePoint&& _waveCheckingTime>=0.3f)
	{
		_waveCheckingTime = 0.0f;
		_state->NextState(eState::STATE_IDLE);
		Map* map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();
		map->destroythisLayerComponent(eTileLayer::TileLayer_OVER);
	}
}
void SelfMoveObject::ClearPathTileCellStack()
{
	while (0 != _pathTileCellStack.size())
	{
		_pathTileCellStack.pop();
	}
}