#include "Equip_item_Body.h"

Equip_item_Body::Equip_item_Body(std::wstring name):Equip_Item(name)
{
	_equipType = eEquipItemType::EquipItem_SHOULDER;
}

Equip_item_Body::~Equip_item_Body()
{
}
void Equip_item_Body::Init(WCHAR * TableFileName, Position tilePosition)
{
	Equip_Item::Init(TableFileName, tilePosition);
}