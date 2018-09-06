#include"Immediately_Item.h"

#include "SceneManager.h"
#include "GameScene.h"
#include "Map.h"

#include "SelfMoveObject.h"

Immediately_Item::Immediately_Item(std::wstring name) :Item(name)
{
}

Immediately_Item::~Immediately_Item()
{
}
void Immediately_Item::ReciverMessage(MessageFrom msgFrom)
{
	if (L"UseItem" == msgFrom.message)
	{
		if (0 == wcscmp(_name.c_str(), L"Position"))
		{
			//reciver is me!!!

			Map * map = ((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap();


			((SelfMoveObject*)msgFrom.sender)->recoveringHp(_effectPower);

			map->destroyComponent(_tilePosition, msgFrom.reciver);
		}
	}
}