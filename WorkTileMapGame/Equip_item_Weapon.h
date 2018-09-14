#pragma once
#include "Equip_Item.h"
class Equip_item_Weapon : public Equip_Item
{
public:
	Equip_item_Weapon(std::wstring name);
	~Equip_item_Weapon();


	void Init(WCHAR * TableFileName, Position tilePosition);

};