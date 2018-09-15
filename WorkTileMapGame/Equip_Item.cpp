#include "Equip_Item.h"
#include "MessageFrom.h"
#include "SelfMoveObject.h"

#include "SceneManager.h"
#include "GameScene.h"
#include "Map.h"

#include "ResourceManager.h"
#include <reader.h>

#include "Equip_item_Weapon.h"
Equip_Item::Equip_Item(std::wstring name) :Item(name)
{
	_equipType = eEquipItemType::EquipItem_NONE;
}

Equip_Item::~Equip_Item()
{
}
void Equip_Item::Init(WCHAR * TableFileName, Position tilePosition)
{
	WCHAR itemtypename[256];
	wsprintf(itemtypename, L"./sprite/item/%s/", _name.c_str());

	InitScriptData(TableFileName);

	WCHAR textureFileName[256];
	WCHAR scriptFileName[256];

	wsprintf(textureFileName, L"%s.png", _name.c_str());
	wsprintf(scriptFileName, L"%s.json", _name.c_str());

	{
		WCHAR tmp[256];
		wcscpy(tmp, itemtypename);
		wcscat(tmp, scriptFileName);
		wcscpy(scriptFileName, tmp);
	}
	{
		WCHAR tmp[256];
		wcscpy(tmp, itemtypename);
		wcscat(tmp, textureFileName);
		wcscpy(textureFileName, tmp);
	}



	_sprite = new Sprite(textureFileName, scriptFileName);
	_sprite->Init();

	_tilePosition = tilePosition;
}
void Equip_Item::InitScriptData(WCHAR * TableFileName)
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
}
void Equip_Item::Decrease(float cutdurability)
{
	_durabilityPoint -= cutdurability;
	if (_durabilityPoint <= 0)
	{
		Map * map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();
		map->destroyComponent(_tilePosition, this);
	}
}
void Equip_Item::Update(float deltaTime)
{
	_sprite->Update(deltaTime);
}

void Equip_Item::render()
{
	Item::render();
}

void Equip_Item::ReciverMessage(MessageFrom msgFrom)
{
	if (L"UseItem" == msgFrom.message)
	{
		Map * map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();

		map->removeComponent(this->GetTilePosition(), this);

		msgFrom.sender->EquipItem(this);
	}
}