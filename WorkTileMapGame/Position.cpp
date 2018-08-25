#include "Position.h"
#include "SelfMoveObject.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Map.h"
Position GetNextTilePosition(Position  currentTilePos, eDirection direction)
{
	Position tilePosition = currentTilePos;
	switch (direction)
	{
	case eDirection::DIRCTION_LEFT:
		tilePosition.x--;
		break;
	case eDirection::DIRCTION_RIGHT:
		tilePosition.x++;
		break;
	case eDirection::DIRCTION_UP:
		tilePosition.y--;
		break;
	case eDirection::DIRCTION_DOWN:
		tilePosition.y++;
		break;
	}
	if (tilePosition.x < 0)
		tilePosition.x = 0;
	if (tilePosition.y < 0)
		tilePosition.y = 0;
	if (((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap()->GetWidth() <= tilePosition.x)
		tilePosition.x--;
	if (((GameScene*)SceneManager::GetInstance()->GetScene())->GetMap()->GetHeight() <= tilePosition.y)
		tilePosition.y--;
	return tilePosition;
}