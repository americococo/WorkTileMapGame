#pragma once
#include "Equip_Item.h"
class Equip_item_Shoulder :public Equip_Item
{
public:
	Equip_item_Shoulder(std::wstring name);
	~Equip_item_Shoulder();

	void Init(WCHAR * TableFileName, Position tilePosition);
private:

};
