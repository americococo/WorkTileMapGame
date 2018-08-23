#include "Item.h"


#include "SceneManager.h"
#include "GameScene.h"
#include "Map.h"

#include "ResourceManager.h"
#include <reader.h>

#include "DataFrom.h"


#include "SceneManager.h"
#include "GameScene.h"
#include <wchar.h>

#include "SelfMoveObject.h"
Item::Item(std::wstring name)
{
	_name = name;
	_objectType = eObjectType::OBJECT_TYPE_ITEM;
}


Item::~Item()
{
}
void Item::Init(WCHAR * TableFileName, Position tilePosition)
{
	std::vector<std::string> ScriptList = ResourceManager::GetInstance()->LoadScript(TableFileName);

	for (int i = 0; i < ScriptList.size(); i++)
	{
		std::string record = ScriptList[i];

		//Sinfile.getline(inputBuffer, 100);

		Json::Value root;
		Json::Reader reader;

		bool isSuccess = reader.parse(record, root);
		if (isSuccess)
		{		
			std::string name = root["ItemName"].asString();
			_name.clear();
			_name.assign(name.begin(), name.end());
			_tileLayer = (eTileLayer)root["layer"].asInt();
			_effectPower = root["EffectPower"].asInt();
		}
	}

	WCHAR textureFileName[256];
	WCHAR scriptFileName[256];

	wsprintf(textureFileName, L"./sprite/item/%s.png",_name.c_str());
	wsprintf(scriptFileName, L"./sprite/item/%s.json",_name.c_str());

	_sprite = new Sprite(textureFileName, scriptFileName);
	_sprite->Init();

	_tilePosition = tilePosition;
}
void Item::Update(float deltaTime)
{
	_sprite->Update(deltaTime);
}
void Item::render()
{
	_sprite->setPostition(_posX, _posY);
	_sprite->render();
}
void Item::DeInit()
{
	_sprite->deInit();
}

void Item::ReciverMessage(MessageFrom msgFrom)
{
	if (L"UseItem" == msgFrom.message)
	{
		if(0==wcscmp(_name.c_str(), L"Position"))
		{
			//reciver is me!!!

			Map * map= ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();
			

			((SelfMoveObject*)msgFrom.sender)->recovering(_effectPower);

			map->destroyComponent(_tilePosition,msgFrom.reciver);
			
		}
	}
}