#pragma once
#include "State.h"
class MOVE_State : public State
{
public:
	MOVE_State();
	~MOVE_State();

	void Start();
	void Stop();
	void Update(float deltaTime);
	void render();
	void DeInit();
};

