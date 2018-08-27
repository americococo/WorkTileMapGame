#pragma once
#include "SelfMoveObject.h"
class Monster :	public SelfMoveObject
{
public:
	Monster(std::wstring name);
	~Monster();


	void Init(WCHAR * TableFileName, Position tilePosition);
	void UpdateMove();

	void InitState();
};

