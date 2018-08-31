#include "MessagePost.h"

#include "MessageFrom.h"

#include "TileObject.h"
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

		if (nullptr != messageMail.reciver)
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
