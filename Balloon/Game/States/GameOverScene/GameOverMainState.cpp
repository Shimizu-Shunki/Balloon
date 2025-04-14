// ============================================
// 
// ファイル名: GameOverMainState.h
// 概要: ゲームオーバーシーンのメイン処理ステート
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/GameOverScene/GameOverMainState.h"
#include "Framework/AudioManager.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Message/SceneMessenger.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameOverMainState::GameOverMainState()
{
	// 入力マネージャーのインスタンスを入力
	m_inputManager = InputManager::GetInstance();
}


/// <summary>
/// 初期処理
/// </summary>
void GameOverMainState::PreUpdate()
{
	
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void GameOverMainState::Update(const float& deltaTime)
{
	(void)deltaTime;

	// Zを入力したらプレイシーンへ以降
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// SEを再生
		AudioManager::GetInstance()->PlaySE(XACT_WAVEBANK_SOUNDS_MOVE, 0.2f);
		// メッセージを送信
		SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT);
	}
}

/// <summary>
/// 終了処理
/// </summary>
void GameOverMainState::PostUpdate()
{

}