#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Framework/SceneManager.h"
#include "Interface/IScene.h"
#include "Game/Scenes/Header/PlayScene.h"
#include "Game/Scenes/Header/TitleScene.h"
#include "Game/Scenes/Header/PlayScene.h"

SceneManager::SceneManager()
	:
	m_nextScene{}
{
	m_commonResources = CommonResources::GetInstance();
}

void SceneManager::Initialize()
{
	// 初期シーンの作成
	m_currentScene = std::make_unique<TitleScene>();
	// 初期シーンの初期化
	m_currentScene->Initialize();

	// 描画マネージャーのモデル達を準備段階から移動
	m_commonResources->GetRenderManager()->CommitPendingDrawables();

	// 初期シーンのスタート処理
	m_currentScene->Start();

	m_isChange = false;
}

void SceneManager::Update(DX::StepTimer const& timer)
{
	if (m_currentScene != nullptr)
		m_currentScene->Update();
}

void SceneManager::Render()
{
	if (m_currentScene != nullptr)
		m_currentScene->Render();
}

void SceneManager::Finalize()
{
	if (m_currentScene != nullptr)
		m_currentScene->Finalize();
}


void SceneManager::CheckChageScene()
{
	if (m_isChange)
	{
		// 前のシーンを削除する
		m_currentScene.reset();
		// 次のシーンを入れる
		m_currentScene = std::move(m_nextScene);
		// 次のシーンスタート処理
		m_currentScene->Start();
		// フラグを解除する
		m_isChange = false;
	}
}