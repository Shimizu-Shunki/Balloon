#pragma once
#include "Interface/ISprite.h"
#include <unordered_map>
#include <shared_mutex>
#include "Interface/IObject.h"
#include "Game/ShadowMap/CascadedShadowMap.h"
#include "Game/Sky/SkyBox.h"
#include "Game/Model3D/Model3D.h"


// 全てのモデル、UIの描画を行うクラス

class Transform;
class CameraManager;
class CascadedShadowMap;
class Model3D;
class SkyBox;
class Image;

class RenderManager
{
public:
	// 描画用モデルを設定
	void AddModel(Model3D* model)
	{ 
		// モデルのエフェクト情報を更新する
		model->GetModel()->UpdateEffects([](DirectX::IEffect* effect) {
			// ベーシックエフェクトを設定する
			DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				// 拡散反射光
				DirectX::SimpleMath::Color diffuseColor = DirectX::SimpleMath::Color(1.0f, 0.95f, 0.9f);
				// ライトが照らす方向
				DirectX::SimpleMath::Vector3 lightDirection(0.0f, 1.0f, 0.0f);
			
				basicEffect->SetLightEnabled(1, false);
				basicEffect->SetLightEnabled(2, false);

				// ゼロ番のライトに拡散反射光を設定する
				basicEffect->SetLightDiffuseColor(0, diffuseColor);
				// ゼロ番のライトが照らす方向を設定する
				basicEffect->SetLightDirection(0, lightDirection);
			}
			});


		m_pendingModels.push_back(model); 
	}
	// スプライトを追加
	void AddSprite(Image* sprite) { m_pendingSprite.push_back(sprite); }

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
	// サンプラーステートの作成
	void CreateSmplerState();


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
	// サンプラーステート
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplerState;
	// 入力レイアウト
	ID3D11InputLayout* m_spriteInputLayout;

	// UIの頂点バッファオブジェクト
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_UIvertexBuffer;
	// 頂点シェーダー
	ID3D11VertexShader* m_UIvertexShader;
	// ジオメトリシェーダー
	ID3D11GeometryShader* m_UIGeometryShader;

	// 2Dのマテリアルを格納
	std::vector<Image*> m_sprite;
	// 2D マテリアルの準備段階データ
	std::vector<Image*> m_pendingSprite;

	
	// カスケードシャドウマップ　まだカスケードされていない
	std::unique_ptr<CascadedShadowMap> m_shadowMap;

	// モデル
	std::vector<Model3D*> m_models;
	// モデル　準備段階データ
	std::vector<Model3D*> m_pendingModels;

	// スカイボックス
	std::unique_ptr<SkyBox> m_skyBox;
	// ディレクショナルライト
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_ambientLightBuffer;
	
};