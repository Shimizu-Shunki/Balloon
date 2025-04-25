#pragma once
#include "Game/Message/Message.h"
#include "Framework/InputManager.h"

class IObserver
{
public:
	// ���b�Z�[�W���󂯎��
	virtual void OnMessegeAccepted(Message::MessageID messageID) = 0;
	// �L�[����������ꂽ�玞�ɌĂяo�����
	virtual void OnKeyPressed(KeyType type , const DirectX::Keyboard::Keys& key) = 0;
};