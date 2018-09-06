#pragma once
#include <Windows.h>
#include "TileObject.h"
#include "Position.h"
class Object : public TileObject
{
public:
	Object(std::wstring name);
	~Object();


	virtual void Init(WCHAR * TableFileName,Position tilePosition)=0;

};

