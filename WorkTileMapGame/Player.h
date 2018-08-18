#pragma once
#include "SelfMoveObject.h"
#include <string>
enum eTileLayer;
struct Position;

class Player : 	public SelfMoveObject
{
public:

	Player(std::wstring name);
	~Player();


	void Init(WCHAR * TableFileName, Position tilePosition);

	void UpdateMove();
};

