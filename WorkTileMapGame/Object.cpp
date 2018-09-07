#include "Object.h"
#include "Equip_Item.h"

Object::Object(std::wstring name)
{
	_name = name;
	_EquipItemWearing.clear();
}

Object::~Object()
{
	
}
void Object::EquipItem(Equip_Item * equipItem)
{
	_EquipItemWearing[equipItem->GetEquipItemType()] = equipItem;
}