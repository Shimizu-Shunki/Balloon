#include "Framework/pch.h"
#include "Game/States/GameClearScene/GameClearMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Message/SceneMessenger.h"

// コンストラクタ
GameClearMainState::GameClearMainState()
{
	// 入力マネージャーのインスタンスを入力
	m_inputManager = InputManager::GetInstance();
}

// デストラクタ
GameClearMainState::~GameClearMainState()
{

}

// 初期化処理
void GameClearMainState::PreUpdate()
{
	
}

// 更新処理
void GameClearMainState::Update(const float& deltaTime)
{
	// スペースを入力したらプレイシーンへ以降
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// メッセージを送信
		SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT);
	}
}

// 終了処理
void GameClearMainState::PostUpdate()
{

}