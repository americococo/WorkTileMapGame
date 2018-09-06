#pragma once
#include "Item.h"
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
	Object * _Owner;
	
public:
	float GetDurabilityPoint() { return _durabilityPoint; }
};

