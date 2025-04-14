// ============================================
// 
// ファイル名: CollisionMessenger.cpp
// 概要: オブジェクトのメッセンジャー（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include <unordered_map>
#include "Game/Message/ObjectMessenger.h"

/// <summary>
/// コンストラクタ
/// </summary>
ObjectMessenger::ObjectMessenger()
	:
	m_objects{},
	m_pendingObjects{}
{

}

/// <summary>
/// オブジェクトを登録
/// </summary>
/// <param name="objectID">オブジェクトID</param>
/// <param name="object">オブジェクト</param>
void ObjectMessenger::Register(int objectID, IObject* object)
{
	// オブジェクトIDとオブジェクトを登録する
	m_pendingObjects.emplace(objectID, object);
}

/// <summary>
/// オブジェクトを解除する
/// </summary>
void ObjectMessenger::Clear()
{
	m_objects.clear();
}

/// <summary>
/// メッセージ送信
/// </summary>
/// <param name="objectID">オブジェクトID</param>
/// <param name="messageID">メッセージID</param>
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

/// <summary>
/// メッセージ送信（メッセージデータを渡せるようにする関数）
/// </summary>
/// <param name="objectID"></param>
/// <param name="messageData"></param>
void ObjectMessenger::Dispatch(int objectID, MessageData messageData)
{

}


void ObjectMessenger::ApplyChanges()
{
	// 現在の物をクリアする
	m_objects.clear();
	// 準備段階のものを反映
	m_objects = m_pendingObjects;
	// 準備段階のものをクリアする
	m_pendingObjects.clear();
}
