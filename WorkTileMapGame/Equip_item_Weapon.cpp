#include "Equip_item_Weapon.h"

Equip_item_Weapon::Equip_item_Weapon(std::wstring name):Equip_Item(name)
{

}

Equip_item_Weapon::~Equip_item_Weapon()
{
}
void Equip_item_Weapon::Init(WCHAR * TableFileName, Position tilePosition)
{
	InitScriptData(TableFileName);

	WCHAR textureFileName[256];
	WCHAR scriptFileName[256];

	wsprintf(textureFileName, L"./sprite/item/Weapon/%s.png", _name.c_str());
	wsprintf(scriptFileName, L"./sprite/item/Weapon/%s.json", _name.c_str());

	_sprite = new Sprite(textureFileName, scriptFileName);
	_sprite->Init();

	_tilePosition = tilePosition;
}