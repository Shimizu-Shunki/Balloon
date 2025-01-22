#pragma once
#include <future>
#include "Shader/2DSpriteShader/Sprite2DShader.h"
#include "Scenes/SceneManager/SceneManager.h"

class SceneManager;
class Sprite2DShader;


class Fade
{
public:

	bool GetIsActive() const { return m_isActive; }

public:

	// コンストラクタ
	Fade();
	// デストラクタ
	~Fade();

public:

	// フェードイン処理
	template <typename T>
	void ChangeSceneFadeIN(float duration) // 任意の秒数を引数で渡す
	{
		// フェード処理中なら処理を終了
		if (m_isActive)
			return;

		m_isActive = true; // フェード処理開始
		m_sprite->SetRuleProgress(0.0f); // アルファ値をシェーダーに設定

		// 次のシーンのロードを準備
		//m_sceneManager->NextSceneLoade<T>([this]() {
		//	// シーンロード後の処理をここに記述可能
		//});
		

		// 非同期タスクを起動
		m_future = std::async(std::launch::async, [this, duration]()
		{
			// 初期アルファ値（完全不透明）
			float alpha = 0.0f;
			// アルファ値の増加量（step を動的に計算）
			const float step = 1.0f / (duration / 0.016f);

			while (alpha < 1.0f)
			{
				alpha += step;
				if (alpha > 1.0f)
				{
					alpha = 1.0f;
				}

				m_sprite->SetRuleProgress(alpha); // アルファ値をシェーダーに設定
				// フレーム待機 (16ms → 60FPS相当)
				std::this_thread::sleep_for(std::chrono::milliseconds(16));
			}

			// フェードを非アクティブ
			m_isActive = false;

			// シーンを切り替える
			//m_sceneManager->ChageScene();
		});
	}


	// フェードアウト処理
	//bool FadeOUT();

	void FadeOUT(float duration)
	{
		// フェード処理中なら処理を終了
		if (m_isActive)
			return;

		m_isActive = true; // フェード処理開始
		m_sprite->SetRuleProgress(1.0f); // アルファ値をシェーダーに設定

		// 非同期タスクを起動
		m_future = std::async(std::launch::async, [this, duration]()
		{
			// 初期アルファ値（完全不透明）
			float alpha = 1.0f;
			// アルファ値の減少量（step を動的に計算）
			const float step = 1.0f / (duration / 0.016f);

			while (alpha > 0.0f)
			{
				alpha -= step;
				if (alpha < 0.0f)
				{
					alpha = 0.0f;
				}

				m_sprite->SetRuleProgress(alpha); // アルファ値をシェーダーに設定
				// フレーム待機 (16ms → 60FPS相当)
				std::this_thread::sleep_for(std::chrono::milliseconds(16));
			}

			// フェードを非アクティブ
			m_isActive = false;
		});
	}


	// 描画する
	void Render();

	private:

		// シーンマネージャー
		SceneManager* m_sceneManager;
		// フェード用テクスチャ
		std::unique_ptr<Sprite2DShader> m_sprite;
		// 非同期タスク管理用
		std::future<void> m_future;
		
		// フェード時間
		float m_fadeTime;
		// フェードアクティブ
		bool m_isActive;


};