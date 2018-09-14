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

	virtual void Init(WCHAR * TableFileName, Position tilePosition);
	virtual void render();
	virtual void Update(float deltaTime);

	
protected:
	float _durabilityPoint;
	
	eEquipItemType _equipType;

	void InitScriptData(WCHAR * TableFileName);
public:
	float GetDurabilityPoint() { return _durabilityPoint; }
	eEquipItemType GetEquipItemType() { return _equipType; }


};

