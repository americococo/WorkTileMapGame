#pragma once
#include <Windows.h>
#include "TileObject.h"
#include "Position.h"
#include <map>
#include "LevelInfo.h"
class Equip_Item;
enum eEquipItemType;
class Object : public TileObject
{
public:
	Object(std::wstring name);
	~Object();


	virtual void Init(WCHAR * TableFileName,Position tilePosition)=0;


protected:
	sLevelInfo _levelInfo;
	std::map<eEquipItemType ,Equip_Item*> _EquipItemWearing;
public:
	void EquipItem(Equip_Item * equipItem);

protected:
	int _activePoint;
	int _maxActivePoint;
public:
	int GetMaxActivePoint() { return _maxActivePoint; }
	int GetActivePoint() { return _activePoint; }
};

