// 海の表現を行うマテリアル

#include "Framework/pch.h"
#include "Game/Material/SeaMaterial.h"
#include "Framework/CommonResources.h"
#include <Framework/Microsoft/ReadData.h>
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"


SeaMaterial::SeaMaterial()
{
	// インスタンスを取得する
	m_commonResources = CommonResources::GetInstance();
	m_time = 0.0f;
}

SeaMaterial::~SeaMaterial()
{
}

void SeaMaterial::Initialize()
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	
	m_states = std::make_unique<DirectX::DX11::CommonStates>(device);

	m_texture = m_commonResources->GetResources()->GetTextureResources()->GetSeaTexture();

	// シェーダを取得する
	m_vertexShader = m_commonResources->GetResources()->GetShaderResources()->GetSeaVS();
	m_hullShader   = m_commonResources->GetResources()->GetShaderResources()->GetSeaHS();
	m_domainShader = m_commonResources->GetResources()->GetShaderResources()->GetSeaDS();
	m_pixelShader  = m_commonResources->GetResources()->GetShaderResources()->GetSeaPS();

	m_inputLayout = m_commonResources->GetResources()->GetShaderResources()->GetSeaInputLayout();

	// ブレンドステートの作成
	CreateBlendState(device);
	// 深度ステンシルステートの作成
	CreateDepthStencilState(device);
	// ラスタライザーステートの作成
	CreateRasterizerState(device);

	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);

	// 頂点データを定義（4つの制御点）
	DirectX::VertexPositionTexture vertex[4] =
	{
		{ DirectX::XMFLOAT3(-2000.0f, -0.0f,  2000.0f), DirectX::XMFLOAT2(0.0f, 0.0f) }, // 左上
		{ DirectX::XMFLOAT3( 2000.0f, -0.0f,  2000.0f), DirectX::XMFLOAT2(1.0f, 0.0f) }, // 右上
		{ DirectX::XMFLOAT3( 2000.0f, -0.0f, -2000.0f), DirectX::XMFLOAT2(1.0f, 1.0f) }, // 右下
		{ DirectX::XMFLOAT3(-2000.0f, -0.0f, -2000.0f), DirectX::XMFLOAT2(0.0f, 1.0f) }  // 左下
	};

	// 頂点バッファの説明
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(DirectX::VertexPositionTexture) * _countof(vertex); // 頂点データ全体のサイズ
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;

	// 頂点データの初期化
	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = vertex;

	device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);

	m_index = 6.0f;
}

void SeaMaterial::Render()
{
	m_time += 0.006f;

	m_index = 100.0f;

	ID3D11DeviceContext1* context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3::Down * 100.0f);

	//	シェーダーに渡す追加のバッファを作成する。(ConstBuffer）
	ConstBuffer cbuff;
	cbuff.matView = m_commonResources->GetCameraManager()->GetViewMatrix().Transpose();
	cbuff.matProj = m_commonResources->GetCameraManager()->GetProjectionMatrix().Transpose();
	cbuff.matWorld = world.Transpose();
	cbuff.Diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);
	cbuff.TessellationFactor = DirectX::SimpleMath::Vector4(m_index, m_time, 10.0f, 0.0f);

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// 入力レイアウトを設定
	context->IASetInputLayout(m_inputLayout);

	// 頂点バッファを設定
	ID3D11Buffer* buffers[] = { m_vertexBuffer.Get() };
	UINT stride[] = { sizeof(DirectX::VertexPositionTexture) };
	UINT offset[] = { 0 };
	context->IASetVertexBuffers(0, 1, buffers, stride, offset);


	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(1, 1, cb);
	context->HSSetConstantBuffers(1, 1, cb);
	context->DSSetConstantBuffers(1, 1, cb);
	context->PSSetConstantBuffers(1, 1, cb);

	// サンプラーステートをピクセルシェーダーに設定
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	// ブレンドステートを設定 (半透明描画用)
	context->OMSetBlendState(m_blendState.Get(), nullptr, 0xFFFFFFFF);
	// 深度ステンシルステートを設定 (深度バッファの書き込みと参照)
	//context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);


	

	// プリミティブトポロジーを設定
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);

	//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//	深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// ラスタライザーステートの設定
	context->RSSetState(m_rasterizerState.Get());

	//	シェーダをセットする
	context->VSSetShader(m_vertexShader,nullptr, 0);
	context->HSSetShader(m_hullShader,  nullptr, 0);
	context->DSSetShader(m_domainShader,nullptr, 0);
	context->PSSetShader(m_pixelShader, nullptr, 0);

	// ピクセルシェーダーにテクスチャリソースを設定
	context->PSSetShaderResources(0, 1, &m_texture);

	// 描画コール
	context->Draw(4, 0);

	//	シェーダの登録を解除しておく
	context->VSSetShader(nullptr, nullptr, 0);
	context->HSSetShader(nullptr, nullptr, 0);
	context->DSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	
}

// ブレンドステートの作成
void SeaMaterial::CreateBlendState(ID3D11Device1* device)
{
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = FALSE;  // カバレッジをアルファに基づいて有効化する
	blendDesc.IndependentBlendEnable = FALSE; // 複数のレンダーターゲットを独立して設定する

	D3D11_RENDER_TARGET_BLEND_DESC rtBlendDesc = {};
	rtBlendDesc.BlendEnable = TRUE;              // ブレンドを有効化
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
}

// 深度ステンシルステートの作成
void SeaMaterial::CreateDepthStencilState(ID3D11Device1* device)
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = TRUE;                          // 深度テストを有効化
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 深度バッファの書き込みを有効化
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;      // 深度テスト条件 (小さい場合のみ描画)
	depthStencilDesc.StencilEnable = FALSE;                       // ステンシルテストを無効化

	// 深度ステンシルステートを作成
	device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
}

// ラスタライザーステートの作成
void SeaMaterial::CreateRasterizerState(ID3D11Device1* device)
{
	D3D11_RASTERIZER_DESC rasterDesc = {};
	rasterDesc.FillMode = D3D11_FILL_SOLID;      // 塗りつぶし (または D3D11_FILL_WIREFRAME)D3D11_FILL_SOLID
	rasterDesc.CullMode = D3D11_CULL_FRONT;       // カリングなし (または D3D11_CULL_FRONT / D3D11_CULL_BACK)
	rasterDesc.FrontCounterClockwise = FALSE;    // 時計回りの頂点順序を表面として認識
	rasterDesc.DepthClipEnable = TRUE;           // 深度クリッピングを有効化
	// ラスタライザーステートの作成
	device->CreateRasterizerState(&rasterDesc, &m_rasterizerState);
}