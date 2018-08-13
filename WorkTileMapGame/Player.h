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


	void Init(int activePoint, Position tilePosition, eTileLayer layer);

	void UpdateMove();
};

