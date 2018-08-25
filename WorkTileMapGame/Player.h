#pragma once
#include "SelfMoveObject.h"
#include <string>
enum eTileLayer;
struct Position;
class Font;

class Player : 	public SelfMoveObject
{
public:

	Player(std::wstring name);
	~Player();


	void Init(WCHAR * TableFileName, Position tilePosition);
	void Update(float deltaTime);
	void render();
	void UpdateMove();



	void InitState();
private:
	Font * _font;
};

