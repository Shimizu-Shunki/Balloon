#pragma once
#include "Game/Message/Message.h"

class IObserver
{
public:
	// メッセージを受け取る
	virtual void OnMessegeAccepted(Message::MessageID messageID) = 0;
};