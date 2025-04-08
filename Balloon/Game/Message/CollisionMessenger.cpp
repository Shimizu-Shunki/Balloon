#include "Framework/pch.h"
#include <unordered_map>
#include "Game/Message/CollisionMessenger.h"

CollisionMessenger::CollisionMessenger()
{

}

/// <summary>
/// オブジェクトを登録する
/// </summary>
/// <param name="objectID"></param>
/// <param name="object"></param>
void CollisionMessenger::Register(int objectID, IObject* object)
{
	// オブジェクトIDとオブジェクトを登録する
	m_pendingObjects.emplace(objectID, object);
}

/// <summary>
/// オブジェクトを解除する
/// </summary>
void CollisionMessenger::Clear()
{
	m_objects.clear();
}

/// <summary>
/// シーンにメッセージを送信する
/// </summary>
/// <param name="messageID"></param>
void CollisionMessenger::Dispatch(int objectID, Message::CollisionMessageID messageID, IObject* sender)
{
	// メッセージを送信するオブジェクトを検索する
	auto it = m_objects.find(objectID);
	// メッセージを送信するオブジェクトが見つかった場合
	if (it != m_objects.end())
	{
		// 送信するオブジェクトのメッセージハンドラを呼び出す
		it->second->OnCollisionMessegeAccepted(messageID , sender);
	}
}

IObject* CollisionMessenger::GetObject(int objectID)
{
	// メッセージを送信するオブジェクトを検索する
	auto it = m_objects.find(objectID);

	return it->second;
}

void CollisionMessenger::ApplyChanges()
{
	// 現在の物をクリアする
	m_objects.clear();
	// 準備段階のものを反映
	m_objects = m_pendingObjects;
	// 準備段階のものをクリアする
	m_pendingObjects.clear();
}