#pragma once
#include "IDLE_State.h"
#include <queue>
class TileCell;
class IDLE_State_Monster : public IDLE_State
{
public:
	IDLE_State_Monster();
	~IDLE_State_Monster();



	void Start();
	void Stop();
	void Update(float deltaTime);
private:
	std::queue<TileCell*> _tileQueue;//Å½Áö¿ë

	std::map<int, std::vector<TileCell*>> _serchTile;
};

