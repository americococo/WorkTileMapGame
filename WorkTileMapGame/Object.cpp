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

		switch (item->GetEquipItemType())
		{
		case eEquipItemType::EquipItem_WEAPON: _levelInfo.Attack_Point -= item->GetEffectPower(); break;
		case eEquipItemType::EquipItem_BODY: break;
		case eEquipItemType::EquipItem_SHOES:  _maxActivePoint -= item->GetEffectPower(); break;
		case eEquipItemType::EquipItem_SHOULDER:break;

		}

		item->DeInit();
		delete item;

	}
	_EquipItemWearing[equipItem->GetEquipItemType()] = equipItem;

	switch (equipItem->GetEquipItemType())
	{
	case eEquipItemType::EquipItem_WEAPON: _levelInfo.Attack_Point += equipItem->GetEffectPower(); break;
	case eEquipItemType::EquipItem_BODY:break;
	case eEquipItemType::EquipItem_SHOES: _maxActivePoint += equipItem->GetEffectPower();  break;
	case eEquipItemType::EquipItem_SHOULDER:break;
		
	}
}
Equip_Item *  Object::GetItemInfo()
{
	return _EquipItemWearing[eEquipItemType::EquipItem_WEAPON]; 
}
