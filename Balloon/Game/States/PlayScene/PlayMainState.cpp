#include "Framework/pch.h"
#include "Game/States/PlayScene/PlayMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Player/Header/Player.h"
#include "Game/Enemy/Enemy.h"

// コンストラクタ
PlayMainState::PlayMainState(Player* player, std::vector<Enemy*> enemys)
	:
	m_player(player),
	m_enemys(enemys)
{
	// 入力マネージャーのインスタンスを入力
	m_inputManager = InputManager::GetInstance();
}

// デストラクタ
PlayMainState::~PlayMainState()
{

}

// 初期化処理
void PlayMainState::OnStateEnter(StateController* stateController)
{
	
}

// 更新処理
void PlayMainState::OnStateUpdate(StateController* stateController, const float& deltaTime)
{
	// スペースを入力したらプレイシーンへ以降
	if (m_inputManager->OnKeyDown(InputManager::Keys::C))
	{
		// パラメーターの変更
		stateController->SetParameter("FadeOUT", 1);
	}
	else if (m_inputManager->OnKeyDown(InputManager::Keys::F))
	{
		// パラメーターの変更
		stateController->SetParameter("FadeOUT", 2);
	}

	if (m_player->GetTransform()->GetLocalPosition().y <= -2.0f)
	{
		// パラメーターの変更
		stateController->SetParameter("FadeOUT", 2);
	}

	for (auto enemy : m_enemys)
	{
		if (enemy->GetTransform()->GetLocalPosition().y >= -1.0f)
		{
			return;
		}
	}

	// パラメーターの変更
	stateController->SetParameter("FadeOUT", 1);
}

// 終了処理
void PlayMainState::OnStateExit(StateController* stateController)
{

}