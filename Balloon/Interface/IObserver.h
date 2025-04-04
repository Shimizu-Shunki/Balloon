#pragma once
#include "Game/Message/Message.h"

class IObserver
{
public:
	// オブジェクトメッセージを受け取る
	virtual void OnObjectMessegeAccepted(Message::ObjectMessageID messageID) = 0;
	// 当たり判定メッセージを受け取る
	virtual void OnCollisionMessegeAccepted(Message::CollisionMessageID messageID , IObject* sender) = 0;
};