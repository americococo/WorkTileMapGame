#pragma once
#include <queue>

#include "MessageFrom.h"
class MessagePost
{
public:
	MessagePost();
	~MessagePost();

private:
	std::queue<MessageFrom> _postQueue;

public:

	
	void SendMessageW(const MessageFrom & messageFrom);
	void ProcessMessageQueue();

	void Clear();


	void Update();
};

