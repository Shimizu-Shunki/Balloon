#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/Header/DebugScene.h"
#include "Interface/IScene.h"
#include "Interface/IObject.h"

#include "Game/Cameras/DebugCamera.h"
#include <Framework/Microsoft/ReadData.h>
#include <VertexTypes.h>
#include "Game/Material/PBRLit.h"
#include "Game/Sky/SkyBox.h"

DebugScene::DebugScene()
{
	m_commonResources = CommonResources::GetInstance();
}


DebugScene::~DebugScene()
{

}

void DebugScene::Initialize()
{
	ID3D11Device1* device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// 定数バッファ用のバッファオブジェクトを作成する
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(AmbientLightParameters));	// 16の倍数を指定する
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	DX::ThrowIfFailed(
		device->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer.ReleaseAndGetAddressOf())
	);


	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = FALSE; // カバレッジをアルファに基づいて有効化する
	blendDesc.IndependentBlendEnable = FALSE; // 複数のレンダーターゲットを独立して設定する

	D3D11_RENDER_TARGET_BLEND_DESC rtBlendDesc = {};
	rtBlendDesc.BlendEnable = TRUE;                                   // ブレンドを有効化
	rtBlendDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;        // ソースのアルファ
	rtBlendDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;    // 逆アルファ
	rtBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;           // 加算ブレンド
	rtBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;              // アルファ値のソース
	rtBlendDesc.DestBlendAlpha = D3D11_BLEND_ZERO;             // アルファ値のデスティネーション
	rtBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;           // アルファ値の加算
	rtBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // RGBA全てを有効

	blendDesc.RenderTarget[0] = rtBlendDesc;

	// カスタムブレンドステートを作成
	device->CreateBlendState(&blendDesc, &m_blendState);

	// モデル取得
	m_sphereModel = m_commonResources->GetResources()->GetSphere();
	// モデルのエフェクトを設定する
	/*m_sphereModel->UpdateEffects([&](DirectX::IEffect* effect)
		{
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				basicEffect->SetLightingEnabled(true);
				basicEffect->SetPerPixelLighting(true);
				basicEffect->SetTextureEnabled(true);
				basicEffect->SetVertexColorEnabled(true);
				basicEffect->SetFogEnabled(false);
			}
		}
	);*/
	// コモンステート取得
	m_commonStates = m_commonResources->GetCommonStates();

	// デバッグカメラ
	m_debugCamera = std::make_unique<DebugCamera>();
	m_debugCamera->Initialize(1280, 720);

	// シェーダー
	std::vector<uint8_t> blob;
	// 頂点シェーダをロードする
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\PBRLit_VS.cso");
	DX::ThrowIfFailed(
		device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_vertexShader.ReleaseAndGetAddressOf())
	);

	//	インプットレイアウトの作成
	device->CreateInputLayout(&DirectX::VertexPositionNormalTangentColorTexture::InputElements[0],
		static_cast<UINT>(DirectX::VertexPositionNormalTangentColorTexture::InputElementCount),
		blob.data(), blob.size(),
		m_inputLayout.GetAddressOf());

	// ピクセルシェーダをロードする
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\PBRLit_PS.cso");
	DX::ThrowIfFailed(
		device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_pixelShader.ReleaseAndGetAddressOf())
	);

	// テクスチャロード
	// メインテクスチャ
	DirectX::CreateWICTextureFromFile(
		device, L"Resources\\Textures\\Cow_Color3.png", nullptr, m_mainTexture.ReleaseAndGetAddressOf());
	// ノーマルマップ
	DirectX::CreateWICTextureFromFile(
		device, L"Resources\\Textures\\woodNor.png", nullptr, m_normalMap.ReleaseAndGetAddressOf());
	// スカイマップ
	DirectX::CreateDDSTextureFromFile(
		device, L"Resources\\Textures\\Skybox.dds", nullptr, m_skyMap.ReleaseAndGetAddressOf());

	using namespace DirectX::SimpleMath;

	m_PBRLit = std::make_unique<PBRLit>();
	m_PBRLit->Initialize();
	m_PBRLit->SetBaseColor(DirectX::SimpleMath::Vector4::One);
	m_PBRLit->SetMatallic(1.0f); // 0.3
	m_PBRLit->SetSmoothness(0.0f); // 0.7
	m_PBRLit->SetUseBaseMap(1.0f);
	m_PBRLit->SetUseNormalMap(0.0f);
	m_PBRLit->SetBaseMap(m_mainTexture.Get());
	m_PBRLit->SetNormalMap(m_normalMap.Get());
	m_PBRLit->SetSkyMap(m_skyMap.Get());

	// モデルのエフェクト情報を更新する
	m_sphereModel->UpdateEffects([](DirectX::IEffect* effect) {
		// ベーシックエフェクトを設定する
		DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
		if (basicEffect)
		{
			// 拡散反射光
			Color diffuseColor = Color(0.3231373f, 0.3607844f, 0.3937255f);
			// ライトが照らす方向
			Vector3 lightDirection(0.0f,1.0f,0.0f);

			//// ライトを有効化する
			//// ※モデルクラスではデフォルトで内部的にライトが有効化されている
			//basicEffect->SetLightingEnabled(true);

			// 個別のライトを有効化/無効化する
			basicEffect->SetLightEnabled(0, true);	// デフォルト値で有効
			basicEffect->SetLightEnabled(1, false);
			basicEffect->SetLightEnabled(2, false);

			// ゼロ番のライトに拡散反射光を設定する
			basicEffect->SetLightDiffuseColor(0, diffuseColor);
			// ゼロ番のライトが照らす方向を設定する
			basicEffect->SetLightDirection(0, lightDirection);


		}
	});

	m_skyBox = std::make_unique<SkyBox>();
	m_skyBox->Initialize();
	
}

void DebugScene::Start()
{
	// BGMを再生する
}

void DebugScene::Update()
{
	// カメラを更新
	m_debugCamera->Update();

	m_PBRLit->UpdateConstantBuffer();
	
	m_commonResources->GetCameraManager()->SetViewMatrix(m_debugCamera->GetViewMatrix());

	// GPUが使用するリソースのメモリにCPUからアクセスする際に利用する構造体
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	// コンテキスト
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// 定数バッファをマップする
	context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// 定数バッファに送るデータを準備する
	AmbientLightParameters* cb = static_cast<AmbientLightParameters*>(mappedResource.pData);
	cb->ambientLightColor = DirectX::SimpleMath::Vector3::One;
	cb->ambientLightIntensity = 0.7f;
	// マップを解除する
	context->Unmap(m_constantBuffer.Get(), 0);

	m_skyBox->Update(m_debugCamera->GetViewMatrix(), m_commonResources->GetCameraManager()->GetProjectionMatrix());
}

void DebugScene::Render()
{
	DirectX::DX11::CommonStates* states = m_commonResources->GetCommonStates();
	ID3D11DeviceContext1* context       = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	DirectX::SimpleMath::Matrix world      = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3::Down * 9.0f);
	DirectX::SimpleMath::Matrix view       = m_debugCamera->GetViewMatrix();
	DirectX::SimpleMath::Matrix projection = m_commonResources->GetCameraManager()->GetProjectionMatrix();

	if (!m_vertexShader || !m_pixelShader)
	{
		OutputDebugStringA("Error: Shader not set!\n");
		return;
	}

	// モデル描画
	m_sphereModel->Draw(context, *states, world, view, projection, false, [&]
		{
			// //ブレンドステートを設定 (半透明描画用)
			//context->OMSetBlendState(m_blendState.Get(), nullptr, 0xFFFFFFFF);

			//// インプットレイアウトの設定
			//context->IASetInputLayout(m_inputLayout.Get());

			//// テクスチャの設定
			//std::vector<ID3D11ShaderResourceView*> tex = {
			//	m_mainTexture.Get(),
			//	m_normalMap.Get(),
			//	m_skyMap.Get(),
			//};

			//context->VSSetShaderResources(0, (UINT)tex.size(), tex.data());
			//context->PSSetShaderResources(0, (UINT)tex.size(), tex.data());

			//// シェーダーを設定
			//context->VSSetShader(m_vertexShader.Get() , nullptr, 0);
			//context->PSSetShader(m_pixelShader.Get()  , nullptr, 0);

			//// サンプラーステートを指定する
			//ID3D11SamplerState* sampler[] = { states->LinearWrap() };
			//context->VSSetSamplers(0, 1, sampler);
			//context->PSSetSamplers(0, 1, sampler);
		
		// 定数バッファを指定する
		ID3D11Buffer* cbuf[] = { m_constantBuffer.Get() };
		context->VSSetConstantBuffers(1, 1, cbuf);
		context->PSSetConstantBuffers(1, 1, cbuf);

		m_PBRLit->SetMaterial();
		});

	m_skyBox->Render();
	//m_commonResources->GetRenderManager()->Render();
}


void DebugScene::Finalize()
{

}

