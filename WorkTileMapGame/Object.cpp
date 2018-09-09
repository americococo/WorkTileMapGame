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
	if(nullptr!=_EquipItemWearing[equipItem->GetEquipItemType()])
	{
		Equip_Item * item = _EquipItemWearing[equipItem->GetEquipItemType()];
		item->DeInit();
		delete item;

	}
	_EquipItemWearing[equipItem->GetEquipItemType()] = equipItem;
}