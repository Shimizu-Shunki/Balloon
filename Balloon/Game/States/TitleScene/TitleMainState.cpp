#include "Framework/pch.h"
#include "Game/States/TitleScene/TitleMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"

// コンストラクタ
TitleMainState::TitleMainState()
{
	// 入力マネージャーのインスタンスを入力
	m_inputManager = InputManager::GetInstance();
}

// デストラクタ
TitleMainState::~TitleMainState()
{

}

// 初期化処理
void TitleMainState::OnStateEnter(StateController* stateController)
{
	
}

// 更新処理
void TitleMainState::OnStateUpdate(StateController* stateController, const float& deltaTime)
{
	// スペースを入力したらプレイシーンへ以降
	if (m_inputManager->OnKeyDown(InputManager::Keys::Space))
	{
		// パラメーターの変更
		stateController->SetParameter("FadeOUT", true);
	}
}

// 終了処理
void TitleMainState::OnStateExit(StateController* stateController)
{

}