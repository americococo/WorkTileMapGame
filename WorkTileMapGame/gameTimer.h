#pragma once
class gameTimer
{
public:
	gameTimer();
	~gameTimer();

public:
	void Reset();
	void update();
	float GetDeltaTime();

private:
	double _deltaTime;
	double _secondperCount;//카운트 하나당 시간
	__int64 _prevCount;
};
