#pragma once
#include "State.h"
class Attack_State :
	public State
{
public:
	Attack_State();
	~Attack_State();

	void Start();
	void Stop();
	void Update(float deltaTime);
	void render();
	void DeInit();
};

