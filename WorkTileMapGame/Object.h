#pragma once
#include <Windows.h>
#include "TileObject.h"
#include "Position.h"
class Object : public TileObject
{
public:
	Object();
	~Object();


	virtual void Init(WCHAR * TableFileName,Position tilePosition);
private:

};

