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
	double _secondperCount;//ī��Ʈ �ϳ��� �ð�
	__int64 _prevCount;
};
