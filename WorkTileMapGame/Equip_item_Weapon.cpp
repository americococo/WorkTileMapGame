#include "Equip_item_Weapon.h"

Equip_item_Weapon::Equip_item_Weapon(std::wstring name):Equip_Item(name)
{
	_equipType = eEquipItemType::EquipItem_WEAPON;
}

Equip_item_Weapon::~Equip_item_Weapon()
{
}
void Equip_item_Weapon::Init(WCHAR * TableFileName, Position tilePosition)
{
	Equip_Item::Init(TableFileName, tilePosition);
}