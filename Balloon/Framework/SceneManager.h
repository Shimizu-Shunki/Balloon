#pragma once
#include "Interface/IScene.h"

#include <future>
#include <queue>
#include "StepTimer.h"

// 各シーンのヘッダーファイル
//#include "Scenes/TitleScene/TitleScene.h"
//#include "Scenes/PlayScene/PlayScene.h"
//#include "Scenes/ResultScene/ResultScene.h"
//#include "Scenes/HomeScene/HomeScene.h"

class IScene;
class CommonResources;

class SceneManager
{
public:
	// 初期フレームの時にシーンを変更する
	void ChageScene() { m_isChange = true; }
	// チェックチェンジシーン
	void CheckChageScene();

public:
	void ChageSceneMove(std::unique_ptr<IScene> scene) { m_nextScene = std::move(scene); }


	// シーンを非同期で準備
	template <typename T>
	void PrepareScene() {
		// 非同期タスクでシーンを準備
		m_future = std::async(std::launch::async, [this]() {

			// シーンの作成と初期化
			auto newScene = std::make_unique<T>(this);
			newScene->Initialize(); 
		});
	}


	template <typename T>
	void NextSceneLoade()
	{
		// 次のシーンを作成
		m_nextScene = std::make_unique<T>(this);
		// 次のシーンを初期化する
		m_nextScene->Initialize();
	}

private:
	//	コンストラクタ
	SceneManager();
	//	デストラクタ
	~SceneManager() = default;
public:
	SceneManager(const SceneManager&) = delete;             // コピー禁止
	SceneManager& operator=(const SceneManager&) = delete;  // コピー代入禁止
	SceneManager(const SceneManager&&) = delete;            // ムーブ禁止
	SceneManager& operator=(const SceneManager&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}

public:

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(DX::StepTimer const& timer);
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();
private:

	// 共有リソース
	CommonResources* m_commonResources;

	// シーン
	std::unique_ptr<IScene> m_currentScene;
	// 次のシーン
	std::unique_ptr<IScene> m_nextScene;

	// シーン切り替えフラグ
	bool m_isChange;

	// 非同期タスク管理用
	std::future<void> m_future;
};