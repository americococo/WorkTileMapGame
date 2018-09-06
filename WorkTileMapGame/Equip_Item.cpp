#include "Equip_Item.h"
#include "MessageFrom.h"
#include "SelfMoveObject.h"

#include "SceneManager.h"
#include "GameScene.h"
#include "Map.h"

#include "ResourceManager.h"
#include <reader.h>
Equip_Item::Equip_Item(std::wstring name) :Item(name)
{
	_Owner = nullptr;
}

Equip_Item::~Equip_Item()
{
}
void Equip_Item::Init(WCHAR * TableFileName, Position tilePosition)
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
			std::string name;
			switch (i)
			{
			case 1:
				name = root["ItemName"].asString();
				_name.clear();
				_name.assign(name.begin(), name.end());
				_tileLayer = (eTileLayer)root["layer"].asInt();
				break;
			case 2:
				_effectPower = root["EffectPower"].asInt();
				_durabilityPoint = root["durability"].asInt();
				break;
			}


		}
	}
	WCHAR textureFileName[256];
	WCHAR scriptFileName[256];

	wsprintf(textureFileName, L"./sprite/item/%s.png", _name.c_str());
	wsprintf(scriptFileName, L"./sprite/item/%s.json", _name.c_str());

	_sprite = new Sprite(textureFileName, scriptFileName);
	_sprite->Init();

	_tilePosition = tilePosition;
}

void Equip_Item::Decrease(float cutdurability)
{
	if (_durabilityPoint <= 0)
	{
		Map * map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();
		map->destroyComponent(_tilePosition, this);
	}
}
void Equip_Item::Update(float deltaTime)
{
	if (nullptr != _Owner)
	{
		_tilePosition = _Owner->GetTilePosition();
	}
	_sprite->Update(deltaTime);
}

void Equip_Item::render()
{
	if (nullptr != _Owner)
	{
		_posX = _Owner->GetPositionX();
		_posY = _Owner->GetPositionY();
	}
	Item::render();
}

void Equip_Item::ReciverMessage(MessageFrom msgFrom)
{
	if (L"UseItem" == msgFrom.message)
	{
		_Owner = msgFrom.sender;

		Map * map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();

		map->removeComponent(this->GetTilePosition(), this);
	}
}