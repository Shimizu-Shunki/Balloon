#pragma once
#include <future>
#include "Game/Material/SpriteMaterial.h"
#include "Game/Material/Buffers.h"
#include "Framework/SceneManager.h"
#include "Framework/Resources.h"
#include "Interface/ISprite.h"

#include "Game/Scenes/Header/PlayScene.h"

class CommonResources;

class Fade : ISprite
{
public:

	bool GetIsActive() const { return m_isActive; }
	
	Transform* GetTransform() const override { return m_transform.get(); }

	SpriteMaterial* GetSpriteMaterial() const override { return m_spriteMaterial.get(); }

public:

	// コンストラクタ
	Fade();
	// デストラクタ
	~Fade() override = default;

	void Initialize() override;

	// 更新処理
	void Update();

public:

	void Begin() override { m_spriteMaterial->Begin(); }

	void End() override { m_spriteMaterial->End(); }

	// フェードイン処理
	void FadeIN(float duration);
	// フェードアウト処理　シーン切り替え付き
	template <typename T>
	void ChangeSceneFadeOUT(float duration)
	{
		// フェード処理中なら true を返す
		if (m_isActive) return;

		// フェード時間を設定
		m_duration = duration;

		// ルール画像の進行度を初期化
		m_constBuffer.ruleProgress = 0.0f;
		// ルール画像の反転をしない
		m_constBuffer.ruleInverse = 0;

		// スタート進行度
		m_startProgress = 0.0f;
		// エンド進行度
		m_endProgress = 1.0f;

		// フェード処理をアクティブにする
		m_isActive = true;
	}

	

	private:

		// 共有リソース
		CommonResources* m_commonResources;

		std::unique_ptr<Transform> m_transform;

		// コンテキスト
		ID3D11DeviceContext1* m_context;

		// バッファ
		ConstBuffer m_constBuffer;
		// 頂点バッファ
		VertexBuffer m_vertexBuffer;
		
		// 画像サイズ
		int m_textureSizeW, m_textureSizeH;

		// シーンマネージャー
		SceneManager* m_sceneManager;
		// フェード用マテリアル
		std::unique_ptr<SpriteMaterial> m_spriteMaterial;
		// 非同期タスク管理用
		std::future<void> m_future;

		// フェード時間
		float m_duration;
		// ルール画像の現在の進行度
		float m_curentRuleProgress;
		// 現在の経過時間
		float m_curentTime;
		// スタート　エンド進行度
		float m_startProgress, m_endProgress;
		// フェードアクティブ
		bool m_isActive;

};