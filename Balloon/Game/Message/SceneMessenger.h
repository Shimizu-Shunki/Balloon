#pragma once
#include "Game/Message/Message.h"
#include "Interface/IScene.h"

class SceneMessenger
{
public:
	// シーンを登録する
	void Register(IScene* scene);
	// シーンを解除する
	void Clear();
	// メッセージを送信する
	void Dispatch(Message::SceneMessageID messageID);

private:
	//	コンストラクタ
	SceneMessenger();
	// デストラクタ
	~SceneMessenger() = default;
public:
	SceneMessenger(const SceneMessenger&) = delete;             // コピー禁止
	SceneMessenger& operator=(const SceneMessenger&) = delete;  // コピー代入禁止
	SceneMessenger(const SceneMessenger&&) = delete;            // ムーブ禁止
	SceneMessenger& operator=(const SceneMessenger&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static SceneMessenger* GetInstance()
	{
		static SceneMessenger instance;
		return &instance;
	}

private:
	// シーン
	IScene* m_scene;
};