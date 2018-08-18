#pragma once
class Component;
#include <string>
struct MessageFrom
{
	Component * sender;
	Component * reciver;

	std::wstring message;
};
