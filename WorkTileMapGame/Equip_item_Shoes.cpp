#include "Equip_item_Shoes.h"
Equip_item_Shoes::Equip_item_Shoes(std::wstring name):Equip_Item(name)
{
}

Equip_item_Shoes::~Equip_item_Shoes()
{
}
void Equip_item_Shoes::Init(WCHAR * TableFileName, Position tilePosition)
{
	InitScriptData(TableFileName);

	WCHAR textureFileName[256];
	WCHAR scriptFileName[256];

	wsprintf(textureFileName, L"./sprite/item/Shoes/%s.png", _name.c_str());
	wsprintf(scriptFileName, L"./sprite/item/Shoes/%s.json", _name.c_str());

	_sprite = new Sprite(textureFileName, scriptFileName);
	_sprite->Init();

	_tilePosition = tilePosition;
} 