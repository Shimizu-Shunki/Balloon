// ============================================
// 
// ファイル名: RenderManager.cpp
// 概要: 全てのモデル、UIの描画を行うクラス
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Framework/RenderManager.h"
#include "Framework/CommonResources.h"
#include "Framework/CameraManager.h"
#include "Game/Transform/Transform.h"
#include "Game/ShadowMap/CascadedShadowMap.h"
#include "Framework/Resources/ShaderResources.h"
#include "Game/Model3D/Model3D.h"
#include "Game/Sky/SkyBox.h"
#include "Game/Material/Buffers.h"
#include "Game/Image/Image.h"

/// <summary>
/// コンストラクタ
/// </summary>
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

	// 各ステート作成
	this->CreateSpriteBlendState();
	this->CreateSpriteDepthStencilState();
	this->CreateSpriteRasterizerState();
	this->CreateSmplerState();

	// インプットレイアウトを設定
	m_spriteInputLayout = commonResources->GetResources()->GetShaderResources()->GetUIinputLayout();

	m_shadowMap = std::make_unique<CascadedShadowMap>();
	m_shadowMap->Initialize();

	m_skyBox = std::make_unique<SkyBox>();
	m_skyBox->Initialize();

	// 定数バッファ用のバッファオブジェクトを作成する
	// シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(AmbientLightParameters);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	m_device->CreateBuffer(&bd, nullptr, &m_ambientLightBuffer);
	// ライトの
	AmbientLightParameters ambientLight;
	ambientLight.ambientLightColor = DirectX::SimpleMath::Vector3(0.8, 0.9, 1.0);
	ambientLight.ambientLightIntensity = 0.8f;
	// 定数バッファのデータを更新
	m_context->UpdateSubresource(m_ambientLightBuffer.Get(), 0, NULL, &ambientLight, 0, 0);

	// シェーダーにデータを渡すためのUIのバーテックスバッファの作成
	D3D11_BUFFER_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(UIVertexBuffer);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	m_device->CreateBuffer(&desc, nullptr, &m_UIvertexBuffer);

	m_UIvertexShader = commonResources->GetResources()->GetShaderResources()->GetUI_VS();
	m_UIGeometryShader = commonResources->GetResources()->GetShaderResources()->GetUI_GS();
}


void RenderManager::SwitchRenderbleObjects()
{
	// 現在のオブジェクトを削除する
	m_models.clear();
	// 次のオブジェクトを格納する
	m_models = m_pendingModels;

	for (auto model : m_models)
	{
		model->GetMaterial()->UpdateConstBuffer();
	}

	// 現在のスプライトを削除する
	m_sprite.clear();
	// 次のスプライトを格納する
	m_sprite = m_pendingSprite;

	for (auto sprite : m_sprite)
	{
		sprite->GetMaterial()->UpdateConstBuffer();
	}

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
			model->Render(m_context, m_commonStates, viewMatrix, projectionMatrix, m_ambientLightBuffer.Get());
	}

	// スプライトの描画
	this->SpriteRender();
}


void RenderManager::SpriteRender()
{
	// サンプラーステートをピクセルシェーダーに設定
	ID3D11SamplerState* sampler[1] = { m_samplerState.Get() };
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

	// スプライトの描画
	for (auto sprite : m_sprite)
	{
		if (sprite == nullptr || !sprite->GetIsActive()) continue;

		auto material = sprite->Render(m_context, m_UIvertexBuffer.Get());

		// 頂点シェーダーの設定
		m_context->VSSetShader(m_UIvertexShader, nullptr, 0);
		// ジオメトリシェーダーの設定
		m_context->GSSetShader(m_UIGeometryShader, nullptr, 0);
		// 描画
		m_context->Draw(1, 0);
		// マテリアルの解放
		material->EndMaterial();
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

void RenderManager::CreateSmplerState()
{
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;  // 異方性フィルタで高品質
	samplerDesc.MaxAnisotropy = 16;                 // 最大16倍の異方性フィルタリング
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;  // 繰り返し（U軸）
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;  // 繰り返し（V軸）
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;  // 繰り返し（W軸）
	samplerDesc.MipLODBias = 0.0f;                  // MIPマップのバイアスなし
	samplerDesc.MinLOD = 0;                         // 最小LOD
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;         // 最大LOD（フル解像度）
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS; // 比較なし（通常のテクスチャ用）

	m_device->CreateSamplerState(&samplerDesc, m_samplerState.GetAddressOf());
}