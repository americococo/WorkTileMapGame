#include "MessagePost.h"

#include "MessageFrom.h"

#include "TileObject.h"
MessagePost::MessagePost()
{
}


MessagePost::~MessagePost()
{
}

void MessagePost::SendMessage(const MessageFrom & messageFrom)
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
void MessagePost::AddMessage(MessageFrom messagefrom)
{
	_postQueue.push(messagefrom);
}