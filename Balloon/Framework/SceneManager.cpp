// ============================================
// 
// ファイル名: SceneManager.cpp
// 概要: 各シーンを管理するクラス（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Framework/SceneManager.h"
#include "Framework/CommonResources.h"
#include "Game/Game.h"

// 各シーン
#include "Game/Scenes/DebugScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager()
	:
	m_currentScene{},
	m_nextScene{},
	m_isChange{},
	m_future{}
{
	// 共有リソースのインスタンスを取得する
	m_commonResources = CommonResources::GetInstance();
}

/// <summary>
/// 初期化処理
/// </summary>
void SceneManager::Initialize()
{
	// 初期シーンの作成
	m_currentScene = std::make_unique<DebugScene>();
	// 初期シーンの初期化
	m_currentScene->Initialize();

	// 初期シーンのスタート処理
	m_currentScene->Start();

	m_isChange = false;
	m_isExitGame = false;
}

/// <summary>
/// 更新処理
/// </summary>
void SceneManager::Update()
{
	if (m_currentScene != nullptr)
		m_currentScene->Update();
}
/// <summary>
/// 描画処理
/// </summary>
void SceneManager::Render()
{
	if (m_currentScene != nullptr)
		m_currentScene->Render();
}
/// <summary>
/// 終了処理
/// </summary>
void SceneManager::Finalize()
{
	if (m_currentScene != nullptr)
		m_currentScene->Finalize();
}

/// <summary>
/// シーン切り替え
/// </summary>
bool SceneManager::CheckChageScene()
{
	// ゲーム終了の場合
	if (m_isExitGame)
	{
		return false;
	}

	// シーン切り替えフラグがオンの場合
	if (m_isChange)
	{
		// 前のシーンの終了処理を行う
		m_currentScene->Finalize();
		// 前のシーンを削除する
		m_currentScene.reset();
		// 次のシーンを入れる
		m_currentScene = std::move(m_nextScene);

		// 次のシーンスタート処理
		m_currentScene->Start();

		// フラグを解除する
		m_isChange = false;
	}

	return true;
}