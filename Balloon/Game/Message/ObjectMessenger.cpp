#include "pch.h"
#include "Game/Message/ObjectMessenger.h"

ObjectMessenger::ObjectMessenger()
{

}


// オブジェクトを登録する
void ObjectMessenger::Register(int objectID, IObject* object)
{
	// オブジェクトIDとオブジェクトを登録する
	m_objects.emplace(objectID, object);
}

// オブジェクトにメッセージを送信する
void ObjectMessenger::Dispatch(int objectID, Message::MessageData messageData)
{
	// メッセージを送信するオブジェクトを検索する
	auto it = m_objects.find(objectID);
	// メッセージを送信するオブジェクトが見つかった場合
	if (it != m_objects.end())
	{
		// 送信するオブジェクトのメッセージハンドラを呼び出す
		it->second->OnMessegeAccepted(messageData);
	}
}

// オブジェクトにメッセージを送信する
void ObjectMessenger::Dispatch(int objectID, Message::MessageID messageID)
{
	Message::MessageData messageData(messageID);

	// メッセージを送信するオブジェクトを検索する
	auto it = m_objects.find(objectID);
	// メッセージを送信するオブジェクトが見つかった場合
	if (it != m_objects.end())
	{
		// 送信するオブジェクトのメッセージハンドラを呼び出す
		it->second->OnMessegeAccepted(messageData);
	}
}


// オブジェクトを取得する
IObject* ObjectMessenger::GetObjectI(int objectID)
{
	// メッセージを送信するオブジェクトを検索する
	auto it = m_objects.find(objectID);
	// メッセージを送信するオブジェクトが見つかった場合
	if (it != m_objects.end())
	{
		// オブジェクトを取得する
		return it->second;
	}
	return nullptr;
}