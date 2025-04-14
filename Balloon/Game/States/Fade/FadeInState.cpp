// ============================================
// 
// ファイル名: FadeInState.cpp
// 概要: フェードインのステート
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/Fade/FadeInState.h"
#include "Game/Fade/Fade.h"
#include "Game/Message/SceneMessenger.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="fade">フェード処理</param>
FadeInState::FadeInState(Fade* fade)
{
	// シーンマネージャーのインスタンスを取得する
	m_sceneManager = SceneManager::GetInstance();
	
	m_fade = fade;
}

/// <summary>
/// 初期化処理
/// </summary>
void FadeInState::PreUpdate()
{
	// フェードインを行う
	m_fade->FadeIN(1.0f);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void FadeInState::Update(const float& deltaTime)
{
	(void)deltaTime;

	// フェードの更新を行う
	m_fade->Update();

	if (!m_fade->GetIsActive())
	{
		SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_IN);
	}
}

/// <summary>
/// 終了処理
/// </summary>
void FadeInState::PostUpdate()
{

}