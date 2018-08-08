#include "MOVE_State.h"



MOVE_State::MOVE_State()
{
}


MOVE_State::~MOVE_State()
{
}
void MOVE_State::Start()
{
	State::Start();
}
void MOVE_State::Stop()
{
	State::Stop();
}
void MOVE_State::Update(float deltaTime)
{
	//유사코드
	//direction moveobejcet->getdirection
	//(direction + tile위치값 ) == canmove?
	//true
	//move
	//false
	//not Moving


	State::Update(deltaTime);
}
void MOVE_State::render()
{
	State::render();
}
void MOVE_State::DeInit()
{
	State::DeInit();
}