#include "Framework/pch.h"
#include "Game/States/GameOverScene/GameOverMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Message/SceneMessenger.h"

// コンストラクタ
GameOverMainState::GameOverMainState()
{
	// 入力マネージャーのインスタンスを入力
	m_inputManager = InputManager::GetInstance();
}

// デストラクタ
GameOverMainState::~GameOverMainState()
{

}

// 初期化処理
void GameOverMainState::PreUpdate()
{
	
}

// 更新処理
void GameOverMainState::Update(const float& deltaTime)
{
	// スペースを入力したらプレイシーンへ以降
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// メッセージを送信
		SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT);
	}
}

// 終了処理
void GameOverMainState::PostUpdate()
{

}