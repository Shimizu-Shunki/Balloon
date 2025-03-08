#pragma once
#include "Game/Material/SpriteMaterial.h"
#include "Interface/ISprite.h"
#include <unordered_map>
#include <shared_mutex>
#include "Interface/IObject.h"
#include "Game/ShadowMap/CascadedShadowMap.h"
#include "Game/Sky/SkyBox.h"


// 全てのモデル、UIの描画を行うクラス

class Transform;
class CameraManager;
class CascadedShadowMap;
class Model3D;
class SkyBox;

class RenderManager
{
public:
	// 描画用モデルを設定
	void AddModel(Model3D* model) { m_pendingModels.push_back(model); }
	// スプライトを追加
	void AddSprite(ISprite* sprite) { m_pendingSprite.push_back(sprite); }

public:
	// 描画用格納庫に移動する
	void SwitchRenderbleObjects();

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

	// 2D描画
	void SpriteRender();

private:
	// ブレンドステートの作成
	void CreateSpriteBlendState();
	// 深度ステンシルステートの作成
	void CreateSpriteDepthStencilState();
	// ラスタライザーステートの作成
	void CreateSpriteRasterizerState();


private:
	ID3D11Device1* m_device;
	ID3D11DeviceContext1* m_context;
	DirectX::CommonStates* m_commonStates;

	CameraManager* m_cameraManager;

	// ブレンドステート
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_spriteBlendState;
	// 深度ステンシルステート
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_spriteDepthStencilState;
	// ラスタライザーステート
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_spriteRasterizerState;
	//	コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	// 入力レイアウト
	ID3D11InputLayout* m_spriteInputLayout;

	// 2Dのマテリアルを格納
	std::vector<ISprite*> m_sprite;
	// 2D マテリアルの準備段階データ
	std::vector<ISprite*> m_pendingSprite;


	// カスケードシャドウマップ　まだカスケードされていない
	std::unique_ptr<CascadedShadowMap> m_shadowMap;

	// スカイボックス
	std::unique_ptr<SkyBox> m_skyBox;

	// モデル
	std::vector<Model3D*> m_models;
	// モデル　準備段階データ
	std::vector<Model3D*> m_pendingModels;
};