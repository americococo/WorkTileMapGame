#include "Equip_item_Shoes.h"
#include <wchar.h>
Equip_item_Shoes::Equip_item_Shoes(std::wstring name):Equip_Item(name)
{
	_equipType = eEquipItemType::EquipItem_SHOES;
}

Equip_item_Shoes::~Equip_item_Shoes()
{
}
void Equip_item_Shoes::Init(WCHAR * TableFileName, Position tilePosition)
{
	Equip_Item::Init(TableFileName, tilePosition);
} 