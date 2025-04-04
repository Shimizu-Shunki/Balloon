#include "Framework/pch.h"
#include "Game/States/Fade/FadeInState.h"
#include "Game/Fade/Fade.h"
#include "Game/Message/SceneMessenger.h"

// コンストラクタ
FadeInState::FadeInState(Fade* fade)
{
	// シーンマネージャーのインスタンスを取得する
	m_sceneManager = SceneManager::GetInstance();
	
	m_fade = fade;
}

// デストラクタ
FadeInState::~FadeInState()
{

}

// 初期化処理
void FadeInState::PreUpdate()
{
	// フェードインを行う
	m_fade->FadeIN(1.0f);
}

// 更新処理
void FadeInState::Update(const float& deltaTime)
{
	// フェードの更新を行う
	m_fade->Update();

	if (!m_fade->GetIsActive())
	{
		SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_IN);
	}
}

// 終了処理
void FadeInState::PostUpdate()
{

}