#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Framework/SceneManager.h"
#include "Interface/IScene.h"
#include "Game/Scenes/Header/PlayScene.h"
#include "Game/Scenes/Header/TitleScene.h"
#include "Game/Scenes/Header/PlayScene.h"

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
	m_currentScene = std::make_unique<TitleScene>();
	// 初期シーンの初期化
	m_currentScene->Initialize();

	// 描画マネージャーのモデル達を準備段階から移動
	m_commonResources->GetRenderManager()->SwitchRenderbleObjects();

	m_commonResources->GetCameraManager()->SwitchCameras();

	// 初期シーンのスタート処理
	m_currentScene->Start();

	m_isChange = false;
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
void SceneManager::CheckChageScene()
{
	// シーン切り替えフラグがオンの場合
	if (m_isChange)
	{
		// 前のシーンの終了処理を行う
		m_currentScene->Finalize();
		// 前のシーンを削除する
		m_currentScene.reset();
		// 次のシーンを入れる
		m_currentScene = std::move(m_nextScene);

		// 描画オブジェクトを次のシーンの物に切り替える
		m_commonResources->GetRenderManager()->SwitchRenderbleObjects();
		// カメラを次のシーンの物に切り替える
		m_commonResources->GetCameraManager()->SwitchCameras();

		// 当たり判定を次のシーンの物に切り替える
		// 前のTweenをすべて停止する

		// 次のシーンスタート処理
		m_currentScene->Start();

		// フラグを解除する
		m_isChange = false;
	}
}