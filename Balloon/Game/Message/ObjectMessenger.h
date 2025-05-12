#pragma once
#include "Interface/IObject.h"
#include "Game/Message/Message.h"

class ObjectMessenger
{
public:



public:

	// オブジェクトを取得する
	IObject* GetObjectI(int objectID);
	// オブジェクトを登録する
	void Register(int objectID, IObject* object);
	// メッセージを送信する
	void Dispatch(int objectID, Message::MessageData messageData);

	void Dispatch(int objectID, Message::MessageID messageID);

private:
	//	コンストラクタ
	ObjectMessenger();
	//	デストラクタ
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

private:
	
	// オブジェクトIDとオブジェクトマッピング
	std::unordered_map<int, IObject*> m_objects;
};