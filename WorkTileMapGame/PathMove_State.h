#pragma once
#include <stack>
class TileCell;
#include "State.h"

class PathMove_State : public State
{
public:
	PathMove_State();
	~PathMove_State();

	

public:
	void Start();
	void Stop();
	void Update(float deltaTime);
	void render();
	void DeInit();

private:
	float _movecheckTime;
	std::stack<TileCell*> _pathTileCellStack;
};

