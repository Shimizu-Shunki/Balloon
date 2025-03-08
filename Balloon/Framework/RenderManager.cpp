#include "Framework/pch.h"
#include "Framework/RenderManager.h"
#include "Framework/CommonResources.h"
#include "Framework/CameraManager.h"
#include "Game/Transform/Transform.h"
#include "Game/ShadowMap/CascadedShadowMap.h"
#include "Framework/Resources/ShaderResources.h"
#include "Game/Model3D/Model3D.h"
#include "Game/Sky/SkyBox.h"

RenderManager::RenderManager()
	:
	m_sprite{},
	m_pendingSprite{},
	m_skyBox{},
	m_models{},
	m_pendingModels{}
{
	// 共有リソース
	auto commonResources = CommonResources::GetInstance();
	// デバイス
	m_device = commonResources->GetDeviceResources()->GetD3DDevice();
	// コンテキスト
	m_context = commonResources->GetDeviceResources()->GetD3DDeviceContext();
	// コモンステート
	m_commonStates = commonResources->GetCommonStates();
	// カメラ管理クラス
	m_cameraManager = commonResources->GetCameraManager();

	// コモンステートの作成
	m_states = std::make_unique<DirectX::CommonStates>(m_device);
	// 各ステート作成
	this->CreateSpriteBlendState();
	this->CreateSpriteDepthStencilState();
	this->CreateSpriteRasterizerState();

	// インプットレイアウトを設定
	m_spriteInputLayout = commonResources->GetResources()->GetShaderResources()->GetUIinputLayout();

	m_shadowMap = std::make_unique<CascadedShadowMap>();
	m_shadowMap->Initialize();

	m_skyBox = std::make_unique<SkyBox>();
	m_skyBox->Initialize();
}


void RenderManager::SwitchRenderbleObjects()
{
	// 現在のオブジェクトを削除する
	m_models.clear();
	// 次のオブジェクトを格納する
	m_models = m_pendingModels;

	// 現在のスプライトを削除する
	m_sprite.clear();
	// 次のスプライトを格納する
	m_sprite = m_pendingSprite;

	m_pendingSprite.clear();
	m_pendingModels.clear();
}

void RenderManager::Render()
{
	// プロジェクション行列を取得する
	const DirectX::SimpleMath::Matrix& projectionMatrix = m_cameraManager->GetProjectionMatrix();
	// ビュー行列を取得する
	const DirectX::SimpleMath::Matrix& viewMatrix       = m_cameraManager->GetViewMatrix();

	m_skyBox->Update(viewMatrix,projectionMatrix);
	m_skyBox->Render(m_context,m_commonStates);

	// 影用描画
	m_shadowMap->Begin();
	// モデルの描画
	for (const auto& model : m_models)
	{
		if (model->GetIsShadow() && model->GetObject()->GetIsActive())
			m_shadowMap->Draw(model->GetModel(), m_context, m_commonStates, model->GetObject()->GetTransform()->GetWorldMatrix());
	}
	m_shadowMap->End();

	// モデルの描画
	for (const auto& model : m_models)
	{
		if (model->GetObject()->GetIsActive())
			model->Render(m_context, m_commonStates, viewMatrix, projectionMatrix, {});
	}

	// スプライトの描画
	this->SpriteRender();
}


void RenderManager::SpriteRender()
{
	// スプライトの描画
	for (const auto& sprite : m_sprite)
	{
		if (sprite != nullptr)
		{
			// マテリアルの適応
			sprite->Begin();

			// サンプラーステートをピクセルシェーダーに設定
			ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
			m_context->PSSetSamplers(0, 1, sampler);

			// ブレンドステートを設定 (半透明描画用)
			m_context->OMSetBlendState(m_spriteBlendState.Get(), nullptr, 0xFFFFFFFF);
			// 深度ステンシルステートを設定 (深度バッファの書き込みと参照)
			//context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
			// ラスタライザーステートの設定
			m_context->RSSetState(m_spriteRasterizerState.Get());
			// 入力レイアウトを設定
			m_context->IASetInputLayout(m_spriteInputLayout);

			// プリミティブトポロジーを設定 (ポイントリスト)
			m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

			// 描画
			m_context->Draw(1, 0);
			// マテリアルの解放
			sprite->End();
		}
	}
}



// ブレンドステートの作成
void RenderManager::CreateSpriteBlendState()
{
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable  = FALSE; // カバレッジをアルファに基づいて有効化する
	blendDesc.IndependentBlendEnable = FALSE; // 複数のレンダーターゲットを独立して設定する

	D3D11_RENDER_TARGET_BLEND_DESC rtBlendDesc = {};
	rtBlendDesc.BlendEnable = TRUE;                                   // ブレンドを有効化
	rtBlendDesc.SrcBlend              = D3D11_BLEND_SRC_ALPHA;        // ソースのアルファ
	rtBlendDesc.DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;    // 逆アルファ
	rtBlendDesc.BlendOp               = D3D11_BLEND_OP_ADD;           // 加算ブレンド
	rtBlendDesc.SrcBlendAlpha         = D3D11_BLEND_ONE;              // アルファ値のソース
	rtBlendDesc.DestBlendAlpha        = D3D11_BLEND_ZERO;             // アルファ値のデスティネーション
	rtBlendDesc.BlendOpAlpha          = D3D11_BLEND_OP_ADD;           // アルファ値の加算
	rtBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // RGBA全てを有効

	blendDesc.RenderTarget[0] = rtBlendDesc;

	// カスタムブレンドステートを作成
	m_device->CreateBlendState(&blendDesc, &m_spriteBlendState);
}

// 深度ステンシルステートの作成
void RenderManager::CreateSpriteDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable    = TRUE;                       // 深度テストを有効化
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 深度バッファの書き込みを有効化
	depthStencilDesc.DepthFunc      = D3D11_COMPARISON_LESS;      // 深度テスト条件 (小さい場合のみ描画)
	depthStencilDesc.StencilEnable  = FALSE;                      // ステンシルテストを無効化

	// 深度ステンシルステートを作成
	m_device->CreateDepthStencilState(&depthStencilDesc, &m_spriteDepthStencilState);
}

// ラスタライザーステートの作成
void RenderManager::CreateSpriteRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterDesc = {};
	rasterDesc.FillMode = D3D11_FILL_SOLID;      // 塗りつぶし (または D3D11_FILL_WIREFRAME)
	rasterDesc.CullMode = D3D11_CULL_NONE;       // カリングなし (または D3D11_CULL_FRONT / D3D11_CULL_BACK)
	rasterDesc.FrontCounterClockwise = FALSE;    // 時計回りの頂点順序を表面として認識
	rasterDesc.DepthClipEnable       = TRUE;     // 深度クリッピングを有効化
	// ラスタライザーステートの作成
	m_device->CreateRasterizerState(&rasterDesc, &m_spriteRasterizerState);
}