#pragma once
#include "Item.h"
class Immediately_Item : public Item
{
public:
	Immediately_Item(std::wstring name);
	~Immediately_Item();


	void ReciverMessage(MessageFrom msgFrom);
private:
	
};

