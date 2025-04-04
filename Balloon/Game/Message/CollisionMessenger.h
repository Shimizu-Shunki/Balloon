#pragma once
#include "Game/Message/Message.h"
#include "Interface/IObject.h"

class CollisionMessenger
{
public:
	// オブジェクトを登録する
	void Register(int objectID, IObject* object);
	// オブジェクトを全て解除する
	void Clear();
	// メッセージを送信する
	void Dispatch(int objectID , Message::CollisionMessageID messageID , IObject* sender);

	// 登録したオブジェクトを取得する
	IObject* GetObject(int objectID);

private:
	//	コンストラクタ
	CollisionMessenger();
	// デストラクタ
	~CollisionMessenger() = default;
public:
	CollisionMessenger(const CollisionMessenger&) = delete;             // コピー禁止
	CollisionMessenger& operator=(const CollisionMessenger&) = delete;  // コピー代入禁止
	CollisionMessenger(const CollisionMessenger&&) = delete;            // ムーブ禁止
	CollisionMessenger& operator=(const CollisionMessenger&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static CollisionMessenger* GetInstance()
	{
		static CollisionMessenger instance;
		return &instance;
	}

private:

	// オブジェクトIDとオブジェクトマッピング
	std::unordered_map<int, IObject*> m_objects;

};