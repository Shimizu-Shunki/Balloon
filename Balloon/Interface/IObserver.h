#pragma once
#include "Game/Message/Message.h"

class IObserver
{
public:
	// ���b�Z�[�W���󂯎��
	virtual void OnMessegeAccepted(Message::MessageID messageID) = 0;
};