#pragma once
#include "Equip_Item.h"
class Equip_item_Shoes :public Equip_Item
{
public:
	Equip_item_Shoes(std::wstring name);
	~Equip_item_Shoes();


	void Init(WCHAR * TableFileName, Position tilePosition);
private:

};
