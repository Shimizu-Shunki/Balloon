#pragma once
#include "Game/Message/Message.h"
#include "Interface/IObject.h"

class ObjectMessenger
{
public:
	// オブジェクトを登録する
	void Register(int objectID, IObject* object);
	// オブジェクトを全て解除する
	void Clear();
	// メッセージを送信する
	void Dispatch(int objectID, Message::ObjectMessageID messageID);

private:
	//	コンストラクタ
	ObjectMessenger();
	// デストラクタ
	~ObjectMessenger() = default;
public:
	ObjectMessenger(const ObjectMessenger&) = delete;             // コピー禁止
	ObjectMessenger& operator=(const ObjectMessenger&) = delete;  // コピー代入禁止
	ObjectMessenger(const ObjectMessenger&&) = delete;            // ムーブ禁止
	ObjectMessenger& operator=(const ObjectMessenger&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static ObjectMessenger* GetInstance()
	{
		static ObjectMessenger instance;
		return &instance;
	}

	// 準備段階の物を反映
	void ApplyChanges();

private:

	// オブジェクトIDとオブジェクトマッピング
	std::unordered_map<int, IObject*> m_objects;

	// 準備段階　オブジェクトIDとオブジェクトマッピング
	std::unordered_map<int, IObject*> m_pendingObjects;

};