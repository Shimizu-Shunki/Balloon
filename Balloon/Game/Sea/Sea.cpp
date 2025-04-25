#include "pch.h"
#include "Game/Sea/Sea.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"


Sea::Sea()
	:
	m_inputLayout{},
	m_vertexShader{},
	m_hullShader{},
	m_domainShader{},
	m_pixelShader{},
	m_texture{},
	m_blendState{},
	m_depthStencilState{},
	m_rasterizerState{}
{
	m_commonResources = CommonResources::GetInstance();
	m_resources = Resources::GetInstance();
	m_commonStates = CommonResources::GetInstance()->GetCommonStates();
	m_context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
}


void Sea::Initialize()
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	m_states = std::make_unique<DirectX::DX11::CommonStates>(device);

	// シェーダーを取得する
	m_vertexShader = m_resources->GetShaderResources()->GetVertexShader(VS_ID::Sea_VS);
	m_hullShader   = m_resources->GetShaderResources()->GetHullShader(HS_ID::Sea_HS);
	m_domainShader = m_resources->GetShaderResources()->GetDomainShader(DS_ID::Sea_DS);
	m_pixelShader  = m_resources->GetShaderResources()->GetPixelShader(PS_ID::Sea_PS);
	// インプットレイアウトを取得
	m_inputLayout = m_resources->GetShaderResources()->GetSeaInputLayout();

	// テクスチャを取得する
	m_texture = m_resources->GetTextureResources()->GetTexture(TextureKeyID::Sea);


	//	シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_constantBuffer);

	// 頂点データを定義（4つの制御点）
	DirectX::VertexPositionTexture vertex[4] =
	{
		{ DirectX::XMFLOAT3(-1000.0f, 0.0f,  1000.0f), DirectX::XMFLOAT2(0.0f, 0.0f) }, // 左上
		{ DirectX::XMFLOAT3( 1000.0f, 0.0f,  1000.0f), DirectX::XMFLOAT2(1.0f, 0.0f) }, // 右上
		{ DirectX::XMFLOAT3( 1000.0f, 0.0f, -1000.0f), DirectX::XMFLOAT2(1.0f, 1.0f) }, // 右下
		{ DirectX::XMFLOAT3(-1000.0f, 0.0f, -1000.0f), DirectX::XMFLOAT2(0.0f, 1.0f) }  // 左下
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

	// ブレンドステートの作成
	CreateBlendState(device);
	// 深度ステンシルステートの作成
	CreateDepthStencilState(device);
	// ラスタライザーステートの作成
	CreateRasterizerState(device);

	// 細分度
	m_index = 6.0f;
	// タイム初期化
	m_time = 0.0f;
}

void Sea::Render()
{
	// タイマーの更新
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();
	m_time += elapsedTime;
	// 細分度設定
	m_index = 100.0f;

	// ワールド行列作成
	DirectX::SimpleMath::Matrix world = 
		DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3::Down * 100.0f);

	//	シェーダーに渡す追加のバッファを作成する。
	ConstBuffer cbuff;
	cbuff.matView = m_commonResources->GetViewMatrix().Transpose();
	cbuff.matProj = m_commonResources->GetProjectionMatrix().Transpose();
	cbuff.matWorld = world.Transpose();
	cbuff.Diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);
	cbuff.TessellationFactor = DirectX::SimpleMath::Vector4(m_index, m_time, 10.0f, 0.0f);

	//	受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	m_context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// 入力レイアウトを設定
	m_context->IASetInputLayout(m_inputLayout);

	// 頂点バッファを設定
	ID3D11Buffer* buffers[] = { m_vertexBuffer.Get() };
	UINT stride[] = { sizeof(DirectX::VertexPositionTexture) };
	UINT offset[] = { 0 };
	m_context->IASetVertexBuffers(0, 1, buffers, stride, offset);

	//	シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_constantBuffer.Get() };
	m_context->VSSetConstantBuffers(1, 1, cb);
	m_context->HSSetConstantBuffers(1, 1, cb);
	m_context->DSSetConstantBuffers(1, 1, cb);
	m_context->PSSetConstantBuffers(1, 1, cb);

	// サンプラーステートをピクセルシェーダーに設定
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	m_context->PSSetSamplers(0, 1, sampler);

	// ブレンドステートを設定 (半透明描画用)
	//m_context->OMSetBlendState(m_blendState.Get(), nullptr, 0xFFFFFFFF);

	// プリミティブトポロジーを設定
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);

	//	深度バッファに書き込み参照する
	m_context->OMSetDepthStencilState(m_states->DepthDefault(), 0);
	// ラスタライザーステートの設定
	m_context->RSSetState(m_rasterizerState.Get());


	//	シェーダをセットする
	m_context->VSSetShader(m_vertexShader, nullptr, 0);
	m_context->HSSetShader(m_hullShader, nullptr, 0);
	m_context->DSSetShader(m_domainShader, nullptr, 0);
	m_context->PSSetShader(m_pixelShader, nullptr, 0);

	// ピクセルシェーダーにテクスチャリソースを設定
	m_context->PSSetShaderResources(0, 1, &m_texture);

	// 描画コール
	m_context->Draw(4, 0);

	//	シェーダの登録を解除しておく
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->HSSetShader(nullptr, nullptr, 0);
	m_context->DSSetShader(nullptr, nullptr, 0);
	m_context->PSSetShader(nullptr, nullptr, 0);

	// テクスチャリソースを解放
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	m_context->PSSetShaderResources(0, 1, nullsrv);
}

/// <summary>
/// ブレンドステートの作成
/// </summary>
/// <param name="device">デバイス</param>
void Sea::CreateBlendState(ID3D11Device1* device)
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

/// <summary>
/// 深度ステンシルステートの作成
/// </summary>
/// <param name="device">デバイス</param>
void Sea::CreateDepthStencilState(ID3D11Device1* device)
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = TRUE;                          // 深度テストを有効化
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 深度バッファの書き込みを有効化
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;      // 深度テスト条件 (小さい場合のみ描画)
	depthStencilDesc.StencilEnable = FALSE;                       // ステンシルテストを無効化

	// 深度ステンシルステートを作成
	device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
}

/// <summary>
/// ラスタライザーステートの作成
/// </summary>
/// <param name="device">デバイス</param>
void Sea::CreateRasterizerState(ID3D11Device1* device)
{
	D3D11_RASTERIZER_DESC rasterDesc = {};
	rasterDesc.FillMode = D3D11_FILL_SOLID;      // 塗りつぶし (または D3D11_FILL_WIREFRAME)D3D11_FILL_SOLID
	rasterDesc.CullMode = D3D11_CULL_FRONT;       // カリングなし (または D3D11_CULL_FRONT / D3D11_CULL_BACK)
	rasterDesc.FrontCounterClockwise = FALSE;    // 時計回りの頂点順序を表面として認識
	rasterDesc.DepthClipEnable = TRUE;           // 深度クリッピングを有効化
	// ラスタライザーステートの作成
	device->CreateRasterizerState(&rasterDesc, &m_rasterizerState);
}