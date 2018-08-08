#include "gameTimer.h"
#include <Windows.h>
gameTimer::gameTimer()
	:_secondperCount(0.0), _deltaTime(-1.0), _prevCount(0)//�ʱ�ȭ �Լ� �������� ó�� �ϱ⶧���� ����
{
	
	__int64 countPerSecond;//1�ʴ� ī��Ʈ ����
	QueryPerformanceFrequency((LARGE_INTEGER*)&countPerSecond);//1�ʿ� �ִ� ī��Ʈ�� ������
	//�ý��۳��� �̹� ���ž� ����
	
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