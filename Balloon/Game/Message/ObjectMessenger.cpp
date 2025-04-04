#include "Framework/pch.h"
#include <unordered_map>
#include "Game/Message/ObjectMessenger.h"


ObjectMessenger::ObjectMessenger()
{

}

void ObjectMessenger::Register(int objectID, IObject* object)
{
	// オブジェクトIDとオブジェクトを登録する
	m_objects.emplace(objectID, object);
}

/// <summary>
/// オブジェクトを解除する
/// </summary>
void ObjectMessenger::Clear()
{
	m_objects.clear();
}


void ObjectMessenger::Dispatch(int objectID, Message::ObjectMessageID messageID)
{
	// メッセージを送信するオブジェクトを検索する
	auto it = m_objects.find(objectID);
	// メッセージを送信するオブジェクトが見つかった場合
	if (it != m_objects.end())
	{
		// 送信するオブジェクトのメッセージハンドラを呼び出す
		it->second->OnObjectMessegeAccepted(messageID);
	}
}
