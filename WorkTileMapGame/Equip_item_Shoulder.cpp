#include "Equip_item_Shoulder.h"

Equip_item_Shoulder::Equip_item_Shoulder(std::wstring name):Equip_Item(name)
{
	_equipType = eEquipItemType::EquipItem_SHOULDER;
}

Equip_item_Shoulder::~Equip_item_Shoulder()
{
}
void Equip_item_Shoulder::Init(WCHAR * TableFileName, Position tilePosition)
{
	Equip_Item::Init(TableFileName, tilePosition);
}