// ============================================
// 
// ファイル名: SceneManager.h
// 概要: SceneManager.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include <future>
#include "Interface/IScene.h"

class IScene;
class CommonResources;
class TweenManager;

class SceneManager
{
public:
	// 初期フレームの時にシーンを変更する
	void ChageScene() { m_isChange = true; }
	// チェックチェンジシーン
	void CheckChageScene();

public:
	
	// シーンを非同期で準備
	template <typename T>
	void PrepareScene() {
		// 非同期タスクでシーンを準備
		m_future = std::async(std::launch::async, [this]() {

			// シーンの作成と初期化
			m_nextScene = std::make_unique<T>();
			m_nextScene->Initialize();
		});
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
	void Update();
	// 描画処理
	void Render();
	// 終了処理
	void Finalize();
private:

	// 共有リソース
	CommonResources* m_commonResources;
	// TweenManager
	TweenManager* m_tweenManager;

	// シーン
	std::unique_ptr<IScene> m_currentScene;
	// 次のシーン
	std::unique_ptr<IScene> m_nextScene;

	// シーン切り替えフラグ
	bool m_isChange;

	// 非同期タスク管理用
	std::future<void> m_future;
};