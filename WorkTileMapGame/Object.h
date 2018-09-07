#pragma once
#include <Windows.h>
#include "TileObject.h"
#include "Position.h"
#include <map>
class Equip_Item;
enum eEquipItemType;
class Object : public TileObject
{
public:
	Object(std::wstring name);
	~Object();


	virtual void Init(WCHAR * TableFileName,Position tilePosition)=0;


protected:
	std::map<eEquipItemType ,Equip_Item*> _EquipItemWearing;
public:
	void EquipItem(Equip_Item * equipItem);
};

