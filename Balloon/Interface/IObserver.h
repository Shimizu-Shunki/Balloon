#pragma once
#include "Game/Message/Message.h"

class IObserver
{
public:
	// �I�u�W�F�N�g���b�Z�[�W���󂯎��
	virtual void OnObjectMessegeAccepted(Message::ObjectMessageID messageID) = 0;
	// �����蔻�胁�b�Z�[�W���󂯎��
	virtual void OnCollisionMessegeAccepted(Message::CollisionMessageID messageID , IObject* sender) = 0;
};