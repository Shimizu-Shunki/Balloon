// ============================================
// 
// ファイル名: FadeOutState.cpp
// 概要: フェードアウトのステート
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/Fade/Fade.h"
#include "Game/Scenes/Header/GameClearScene.h"
#include "Game/Scenes/Header/GameOverScene.h"
#include "Game/Scenes/Header/TitleScene.h"
#include "Game/Scenes/Header/MenuScene.h"
#include "Game/Scenes/Header/PlayScene.h"
#include "Game/Scenes/Header/StageSelectScene.h"
#include "Framework/SceneManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="fade">フェード処理</param>
/// <param name="chageSceneID">シーンID</param>
FadeOutState::FadeOutState(Fade* fade, const FadeOutState::ChageSceneID& chageSceneID)
{
	// シーンマネージャーのインスタンスを取得する
	m_sceneManager = SceneManager::GetInstance();
	// シーンID登録
	m_chageSceneId = chageSceneID;
	// フェード処理を取得
	m_fade = fade;
}


/// <summary>
/// 初期処理
/// </summary>
void FadeOutState::PreUpdate()
{
	switch (m_chageSceneId)
	{
		case FadeOutState::ChageSceneID::TITLE_SCENE:
			// 次のシーンの初期化を非同期で実行
			m_sceneManager->PrepareScene<TitleScene>();
			m_fade->ChangeSceneFadeOUT<TitleScene>(1.0f);
			break;
		case FadeOutState::ChageSceneID::MENU_SCENE:
			// 次のシーンの初期化を非同期で実行
			m_sceneManager->PrepareScene<MenuScene>();
			m_fade->ChangeSceneFadeOUT<MenuScene>(1.0f);
			break;
		case FadeOutState::ChageSceneID::SELECT_SCENE:
			// 次のシーンの初期化を非同期で実行
			m_sceneManager->PrepareScene<StageSelectScene>();
			m_fade->ChangeSceneFadeOUT<StageSelectScene>(1.0f);
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
		case FadeOutState::ChageSceneID::EXIT_GAME:
			// ゲーム終了フェードアウト
			m_fade->ExitGameFadeOUT(1.0f);
			break;
		default:
			break;
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void FadeOutState::Update(const float& deltaTime)
{
	(void)deltaTime;

	// フェードの更新
	m_fade->Update();
}

/// <summary>
/// 終了処理
/// </summary>
void FadeOutState::PostUpdate()
{

}