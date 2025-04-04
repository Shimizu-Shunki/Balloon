#include "Framework/pch.h"
#include "Game/States/PlayScene/PlayMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Player/Header/Player.h"
#include "Game/Enemy/Enemy.h"

// コンストラクタ
PlayMainState::PlayMainState(std::vector<IObject*> objects)
{
	// 入力マネージャーのインスタンスを入力
	m_inputManager = InputManager::GetInstance();
	// オブジェクトを取得する
	m_objects = objects;
}

// デストラクタ
PlayMainState::~PlayMainState()
{

}

// 初期化処理
void PlayMainState::PreUpdate()
{
	// オブジェクトを有効化にする
	for (const auto& object : m_objects)
	{
		object->SetIsActive(true);
	}
}

// 更新処理
void PlayMainState::Update(const float& deltaTime)
{
	// オブジェクトの更新を行う
	for (const auto& object : m_objects)
	{
		// 更新処理
		object->Update();
		// Transformの更新処理
		object->GetTransform()->Update();
	}
	// タイマーの更新処理

	// シーン自体の更新
	
}

// 終了処理
void PlayMainState::PostUpdate()
{

}