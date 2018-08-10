#include "IDLE_State.h"


#include "SelfMoveObject.h"
IDLE_State::IDLE_State()
{
}

IDLE_State::~IDLE_State()
{
}

void IDLE_State::Start()
{
	State::Start();
}
void IDLE_State::Stop()
{
	State::Stop();
}
void IDLE_State::Update(float deltaTime)
{
	eDirection direction = eDirection::DIRCTION_NONE;
	
	if (_moveObject->IsActive())
		_moveObject->UpdateMove();

	State::Update(deltaTime);
}
void IDLE_State::render()
{
	State::render();
}
void IDLE_State::DeInit()
{
	State::DeInit();
}