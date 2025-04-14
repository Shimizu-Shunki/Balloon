// ============================================
// 
// ファイル名: StageSelectMainState.cpp
// 概要: ステージセレクトシーンのメイン処理ステート
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/StageSelectScene/StageSelectMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Message/SceneMessenger.h"
#include "Framework/AudioManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
StageSelectMainState::StageSelectMainState()
{
	// 入力マネージャーのインスタンスを入力
	m_inputManager = InputManager::GetInstance();
}

/// <summary>
/// 初期処理
/// </summary>
void StageSelectMainState::PreUpdate()
{
	
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void StageSelectMainState::Update(const float& deltaTime)
{
	(void)deltaTime;

	// 左右キーでステージを選択
	// 左キー押したとき
	if (m_inputManager->OnKeyDown(InputManager::Keys::Left))
	{

	}
	// 右キー押したとき
	if (m_inputManager->OnKeyDown(InputManager::Keys::Right))
	{

	}

	// ESCキーでメニューシーンへ移動
	if (m_inputManager->OnKeyDown(InputManager::Keys::Escape))
	{
		// SEを再生
		AudioManager::GetInstance()->PlaySE(XACT_WAVEBANK_SOUNDS_CANCEL,0.2f);
		// メッセージを送信
		SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_MENU_SCENE);
	}

	// ESCキーでメニューシーンへ移動
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT);
	}
}

/// <summary>
/// 終了処理
/// </summary>
void StageSelectMainState::PostUpdate()
{

}