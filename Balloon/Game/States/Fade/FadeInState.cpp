#include "Framework/pch.h"
#include "Game/States/Fade/FadeInState.h"
#include "Game/Fade/Fade.h"

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
void FadeInState::OnStateEnter(StateController* stateController)
{
	// フェードインを行う
	m_fade->FadeIN(1.0f);
}

// 更新処理
void FadeInState::OnStateUpdate(StateController* stateController, const float& deltaTime)
{
	if (!m_fade->GetIsActive())
	{
		// パラメーターの変更
		stateController->SetParameter("FadeIN", true);
	}
}

// 終了処理
void FadeInState::OnStateExit(StateController* stateController)
{

}