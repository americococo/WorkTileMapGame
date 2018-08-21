#pragma once
class TileObject;
#include <string>

struct MessageFrom
{
	TileObject * sender;
	TileObject * reciver;

	std::wstring message;
};
