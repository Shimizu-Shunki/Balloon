#include "Framework/pch.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/Fade/Fade.h"
#include "Game/Scenes/Header/GameClearScene.h"
#include "Game/Scenes/Header/GameOverScene.h"
#include "Game/Scenes/Header/TitleScene.h"

// コンストラクタ
FadeOutState::FadeOutState(Fade* fade, const FadeOutState::ChageSceneID& chageSceneID)
{
	// シーンマネージャーのインスタンスを取得する
	m_sceneManager = SceneManager::GetInstance();

	m_chageSceneId = chageSceneID;

	m_fade = fade;
}

// デストラクタ
FadeOutState::~FadeOutState()
{

}

// 初期化処理
void FadeOutState::OnStateEnter(StateController* stateController)
{
	switch (m_chageSceneId)
	{
		case FadeOutState::ChageSceneID::TITLE_SCENE:
			// 次のシーンの初期化を非同期で実行
			m_sceneManager->PrepareScene<TitleScene>();
			m_fade->ChangeSceneFadeOUT<TitleScene>(1.0f);
			break;
		case FadeOutState::ChageSceneID::SELECT_SCENE:

			break;
		case FadeOutState::ChageSceneID::PLAY_SCENE:
			
			// 次のシーンの初期化を非同期で実行
			m_sceneManager->PrepareScene<PlayScene>();

			m_fade->ChangeSceneFadeOUT<PlayScene>(1.0f);

			break;
		case FadeOutState::ChageSceneID::GAME_CLEAR_SCENE:
			// 次のシーンの初期化を非同期で実行
			m_sceneManager->PrepareScene<GameClearScene>();
			m_fade->ChangeSceneFadeOUT<GameClearScene>(1.0f);
			break;
		case FadeOutState::ChageSceneID::GAME_OVER_SCENE:
			// 次のシーンの初期化を非同期で実行
			m_sceneManager->PrepareScene<GameOverScene>();
			m_fade->ChangeSceneFadeOUT<GameOverScene>(1.0f);
			break;
		default:
			break;
	}
}

// 更新処理
void FadeOutState::OnStateUpdate(StateController* stateController, const float& deltaTime)
{
	
}

// 終了処理
void FadeOutState::OnStateExit(StateController* stateController)
{

}