#pragma once
class Object;
#include <string>

struct MessageFrom
{
	Object * sender;
	Object * reciver;

	std::wstring message;
};
