#include "gameTimer.h"
#include <Windows.h>
gameTimer::gameTimer()
	:_secondperCount(0.0), _deltaTime(-1.0), _prevCount(0)//초기화 함수 접근전에 처리 하기때무에 빠름
{
	
	__int64 countPerSecond;//1초당 카운트 갯수
	QueryPerformanceFrequency((LARGE_INTEGER*)&countPerSecond);//1초에 최대 카운트수 돌려줌
	//시스템내에 이미 계산돼어 있음
	
	_secondperCount=1.0 /(double)countPerSecond;
}
gameTimer::~gameTimer() {}


void gameTimer::Reset() 
{
	__int64 currentCount;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentCount);

	_prevCount=currentCount;
}
void gameTimer::update()
{
	__int64 currentCount;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentCount);

	_deltaTime = (currentCount - _prevCount)*_secondperCount;
	_prevCount = currentCount;
}
float gameTimer::GetDeltaTime() 
{
	return (float)_deltaTime;
}