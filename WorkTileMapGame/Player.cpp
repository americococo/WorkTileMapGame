#include "Player.h"

#include "TileCell.h"
#include "IDLE_State.h"
#include "MOVE_State.h"
#include "Attack_State.h"
#include "Skill_State.h"

#include "GameScene.h"
#include "SceneManager.h"
#include "Map.h"

#include "GameSystem.h"
#include "Font.h"

#include "Equip_Item.h"

#include <reader.h>
#include "ResourceManager.h"

Player::Player(std::wstring name):SelfMoveObject(name)
{
	_objectType = eObjectType::OBJECT_TYPE_PLAYER;
}


Player::~Player()
{
}
void Player::Init(WCHAR * TableFileName, Position tilePosition)
{
	
	std::vector<std::string> ScriptList = ResourceManager::GetInstance()->LoadScript(TableFileName);

	for (int i = 0; i < ScriptList.size(); i++)
	{
		std::string record = ScriptList[i];

		Json::Value root;
		Json::Reader reader;

		bool isSuccess = reader.parse(record, root);
		if (isSuccess)
		{
			switch (i)
			{
			case 1:
				_maxActivePoint = root["ActivePoint"].asInt();
				_tileLayer = (eTileLayer)root["layer"].asInt();
				break;
			case 2:
				_levelInfo.Health_Point = root["Hp"].asInt();
				_levelInfo.Mana_Point = root["Mp"].asInt();

				_levelInfo.Attack_Point = root["AttackPoint"].asInt();
				_levelInfo.Deffence_Point = root["DeffencePoint"].asInt();
				break;

			}

		}
	}
	 
	_levelInfo.Max_Health_Point = _levelInfo.Health_Point;
	_levelInfo.Max_Mana_Point = _levelInfo.Mana_Point;


	SelfMoveObject::Init(TableFileName, tilePosition);


	InitState();

	D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255);
	_font = new Font(L"comicsans", 15, color);
	_font->SetRect(100, 100, GameSystem::GetInstance()->GetWidth(), 100);

	_levelInfo.Lv = 1;
	_levelInfo.Experience_Point = 1;

	_enemyType = (eObjectType::OBJECT_TYPE_MONSTER);

}
void Player::InitState()
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
	{
		State * state = new Skill_State();
		state->Init(this);
		_stateDirection[eState::STATE_SKILL] = state;
	}

	changeState(eState::STATE_IDLE);
}
void Player::Update(float deltaTime)
{
	SelfMoveObject::Update(deltaTime);


	int durabillity = 0;
	if (nullptr != GetItemInfo())
		durabillity = GetItemInfo()->GetDurabilityPoint();

	WCHAR text[128];
	wsprintf(text, L"LV:%d \n HP :%d // FullHP :%d \n AttackPoint : %d \n Weapon durability:%d ", _levelInfo.Lv, _levelInfo.Health_Point, _levelInfo.Max_Health_Point, (int)_levelInfo.Attack_Point,durabillity);
	_font->setText(text);

}
void Player::render()
{
	SelfMoveObject::render();
	_font->setPosition(0, 0);
	_font->render();
}

void Player::UpdateMove()
{
	eDirection direction = eDirection::DIRCTION_NONE;

	if (GameSystem::GetInstance()->IsKeyDown(VK_LEFT))
		direction = eDirection::DIRCTION_LEFT;
	if (GameSystem::GetInstance()->IsKeyDown(VK_RIGHT))
		direction = eDirection::DIRCTION_RIGHT;
	if (GameSystem::GetInstance()->IsKeyDown(VK_UP))
		direction = eDirection::DIRCTION_UP;
	if (GameSystem::GetInstance()->IsKeyDown(VK_DOWN))
		direction = eDirection::DIRCTION_DOWN;


	if (GameSystem::GetInstance()->IsKeyDown(VK_CONTROL))
	{
		_skillType = SkillType::SKILLTYPE_RANGEATTACK;
		_state->NextState(eState::STATE_SKILL);
	}

	if (eDirection::DIRCTION_NONE != direction)
	{
		_currentDirection = direction;
		_state->NextState(eState::STATE_MOVE);
	}

}