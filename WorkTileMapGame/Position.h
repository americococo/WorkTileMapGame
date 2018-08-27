#pragma once
enum eDirection;
struct Position
{
	int x;
	int y;
};
Position GetNextTilePosition(Position currentTilePos, eDirection direction);
eDirection GetDirection(Position to, Position from);