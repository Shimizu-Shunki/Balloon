#pragma once
#include "Game/Material/SpriteMaterial.h"
#include <unordered_map>

// 全てのモデル、UIの描画を行うクラス

class Transform;
class CameraManager;

class RenderManager
{
public:
	// ワールド行列変換は各クラスで行う

	struct RenderableObject
	{
		// 情報格納されたTransformクラスのポインタ
		 Transform* transform;
		// モデル
		DirectX::Model* model;
		// マテリアル
	};



public:
	// プロジェクション行列を取得する
	DirectX::SimpleMath::Matrix GetProjectionMatrix() const { return m_projectionMatrix; }
	// 描画用モデルを設定
	void AddModel(RenderManager::RenderableObject model) { m_pendingRenderableObjects.push_back(model); }
	// スカイスフィアを登録する
	void SetSkySphereObject(RenderManager::RenderableObject object) { m_skySphere = object; }

public:
	// 描画準備登録
	void RegisterPendingDrawables();
	// 描画用格納庫に移動する
	void CommitPendingDrawables();

private:
	//	コンストラクタ
	RenderManager();
	//	デストラクタ
	~RenderManager() = default;
public:
	RenderManager(const RenderManager&) = delete;             // コピー禁止
	RenderManager& operator=(const RenderManager&) = delete;  // コピー代入禁止
	RenderManager(const RenderManager&&) = delete;            // ムーブ禁止
	RenderManager& operator=(const RenderManager&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static RenderManager* GetInstance()
	{
		static RenderManager instance;
		return &instance;
	}

public:

	// 描画処理
	void Render();


private:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;
	DirectX::CommonStates* m_commonStates;

	CameraManager* m_cameraManager;

	// 2Dのマテリアルを格納
	std::vector<SpriteMaterial*> m_spriteMaterials;
	// 2D マテリアルの準備段階データ
	std::vector<SpriteMaterial*> m_pendingSpriteMaterials;


	// スカイスフィア
	RenderableObject m_skySphere;
	// 3D描画に必要な情報格納構造体
	std::vector<RenderableObject> m_renderableObjects;
	// 3D モデルの準備段階データ
	std::vector<RenderableObject> m_pendingRenderableObjects;

	// プロジェクション行列
	DirectX::SimpleMath::Matrix m_projectionMatrix;
};