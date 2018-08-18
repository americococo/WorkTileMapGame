#include "Item.h"

#include "ResourceManager.h"
#include <reader.h>


Item::Item(std::wstring name)
{
	_name = name;
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