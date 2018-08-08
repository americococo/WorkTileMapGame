#pragma once
#include "State.h"
class IDLE_State :public State
{
public:
	IDLE_State();
	~IDLE_State();

	void Start();
	void Stop();
	void Update(float deltaTime);
	void render();
	void DeInit();
private:

};

