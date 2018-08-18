#include "MessagePost.h"


#include "Component.h"
MessagePost::MessagePost()
{
}


MessagePost::~MessagePost()
{
}

void MessagePost::SendMessageW(const MessageFrom & messageFrom)
{
	_postQueue.push(messageFrom);
}
void MessagePost::ProcessMessageQueue()
{
	while (false==_postQueue.empty())
	{
		MessageFrom messageMail = _postQueue.front();
		_postQueue.pop();
		messageMail.reciver->ReciverMessage(messageMail);
	}
}

void MessagePost::Update()
{
	ProcessMessageQueue();
}

void MessagePost::Clear()
{
	while (0 != _postQueue.size())
	{
		_postQueue.pop();
	}
}