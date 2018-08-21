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

	
	void SendMessage(const MessageFrom & messageFrom);
	void ProcessMessageQueue();

	void Clear();


	void Update();



public:
	void AddMessage(MessageFrom messagefrom);
};

