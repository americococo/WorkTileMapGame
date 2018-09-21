#pragma once
#include "Equip_Item.h"
class Equip_item_Body :public Equip_Item
{
public:
	Equip_item_Body(std::wstring name);
	~Equip_item_Body();

	void Init(WCHAR * TableFileName, Position tilePosition);
private:

};
