// ============================================
// 
// ファイル名: TitleMainState.cpp
// 概要: タイトルシーンのメイン処理ステート
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/TitleScene/TitleMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Message/SceneMessenger.h"
#include "Framework/AudioManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
TitleMainState::TitleMainState()
{
	// 入力マネージャーのインスタンスを入力
	m_inputManager = InputManager::GetInstance();
	m_sceneMessenger = SceneMessenger::GetInstance();
}

/// <summary>
/// 初期処理
/// </summary>
void TitleMainState::PreUpdate()
{
	
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void TitleMainState::Update(const float& deltaTime)
{
	(void)deltaTime;

	// スペースを入力したらプレイシーンへ以降
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// SEを再生
		AudioManager::GetInstance()->PlaySE(XACT_WAVEBANK_SOUNDS_STARTBUTTON);
		
		// メッセージを送信
		m_sceneMessenger->Dispatch(Message::SceneMessageID::FADE_OUT);
	}
}

/// <summary>
/// 終了処理
/// </summary>
void TitleMainState::PostUpdate()
{

}