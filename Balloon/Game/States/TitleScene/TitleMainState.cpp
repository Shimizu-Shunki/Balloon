#include "Framework/pch.h"
#include "Game/States/TitleScene/TitleMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Message/SceneMessenger.h"

// コンストラクタ
TitleMainState::TitleMainState()
{
	// 入力マネージャーのインスタンスを入力
	m_inputManager = InputManager::GetInstance();
	m_sceneMessenger = SceneMessenger::GetInstance();
}

// デストラクタ
TitleMainState::~TitleMainState()
{

}

// 初期化処理
void TitleMainState::PreUpdate()
{
	
}

// 更新処理
void TitleMainState::Update(const float& deltaTime)
{
	// スペースを入力したらプレイシーンへ以降
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// メッセージを送信
		m_sceneMessenger->Dispatch(Message::SceneMessageID::FADE_OUT);
	}
}

// 終了処理
void TitleMainState::PostUpdate()
{

}