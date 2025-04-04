#pragma once
#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"

class CommonResources;
class SceneManager;
class Image;
class IMaterial;
class Transform;
class DefaultUi;

class Fade
{
public:

	bool GetIsActive() const { return m_isActive; }
	
	Transform* GetTransform() const { return m_transform.get(); }

public:

	// コンストラクタ
	Fade();
	// デストラクタ
	~Fade() = default;

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update();

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

		auto material = dynamic_cast<DefaultUi*>(m_material.get());

		// ルール画像の進行度を初期化
		material->SetRuleProgress(0.0f);
		// ルール画像の反転をしない
		material->SetRuleInverse(0.0f);

		// スタート進行度
		m_startProgress = 0.0f;
		// エンド進行度
		m_endProgress = 1.0f;

		// フェード処理をアクティブにする
		m_isActive = true;
	}

	void ExitGameFadeOUT(float duration)
	{
		// フェード処理中なら true を返す
		if (m_isActive) return;

		// フェード時間を設定
		m_duration = duration;

		auto material = dynamic_cast<DefaultUi*>(m_material.get());

		// ルール画像の進行度を初期化
		material->SetRuleProgress(0.0f);
		// ルール画像の反転をしない
		material->SetRuleInverse(0.0f);

		// スタート進行度
		m_startProgress = 0.0f;
		// エンド進行度
		m_endProgress = 1.0f;

		// フェード処理をアクティブにする
		m_isActive = true;

		m_isExitGame = true;
	}

private:
	// マテリアルの初期化処理
	void InitialMaterial(int width, int height);



private:

	// 共有リソース
	CommonResources* m_commonResources;
	// コンテキスト
	ID3D11DeviceContext1* m_context;
	// シーンマネージャー
	SceneManager* m_sceneManager;

	// トランスフォーム
	std::unique_ptr<Transform> m_transform;
	// Image
	std::unique_ptr<Image> m_image;
	// マテリアル
	std::unique_ptr<IMaterial> m_material;

	// テクスチャサイズ
	int m_textureSizeW, m_textureSizeH;
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

	bool m_isExitGame;
};