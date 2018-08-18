#include "Component.h"
Component::Component(std::wstring name)
{
	_name = name;
}

Component::~Component()
{
}
void Component::ReciverMessage(MessageFrom msgFrom)
{
	if (L"Collison" == msgFrom.message)
	{
		//충돌처리
	}
}