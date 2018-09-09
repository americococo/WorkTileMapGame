#pragma once
#include "Item.h"

enum eEquipItemType
{
	EquipItem_WEAPON,
	EquipItem_SHOULDER,
	EquipItem_SHOES,
	EquipItem_BODY,
	EquipItem_NONE,
};

class Equip_Item :public Item
{
public:
	Equip_Item(std::wstring name);
	~Equip_Item();

	void Decrease(float cutdurability);
	void ReciverMessage(MessageFrom msgFrom);

	void Init(WCHAR * TableFileName, Position tilePosition);
	void render();
	void Update(float deltaTime);

	
private:

	float _durabilityPoint;
	
	eEquipItemType _equipType;
public:
	float GetDurabilityPoint() { return _durabilityPoint; }
	eEquipItemType GetEquipItemType() { return _equipType; }
};

