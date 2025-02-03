#include "Framework/pch.h"
#include "Game/Material/SpriteMaterial.h"
#include <Framework/Microsoft/ReadData.h>

/// <summary>
/// インプットレイアウト
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> SpriteMaterial::DEFAULT_INPUT_LAYOUT =
{
	// セマンティック名 インデックス フォーマット                          入力スロット オフセット データ種別                     インスタンスステップ率
		{ "SV_Position",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  0,                                                   D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4 position
		{ "NORMAL",    0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  sizeof(DirectX::SimpleMath::Vector4),                D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 rotate
		{ "TEXCOORD",  0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 scale
		{ "TEXCOORD",  1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4 rect
		{ "COLOR",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 } // float4 color};
};

/// <summary>
/// コンストラクタ
/// </summary>
SpriteMaterial::SpriteMaterial(ID3D11Device1* device, ID3D11DeviceContext1* context)
{
	m_device = device;
	m_context = context;

	m_ruleTexture = nullptr;

		// コモンステートの作成
	m_states = std::make_unique<DirectX::CommonStates>(m_device);

	// シェーダーにデータを渡すためのバーテックスバッファの作成
	D3D11_BUFFER_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(VertexBuffer);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	device->CreateBuffer(&desc, nullptr, &m_vBuffer);

	// ブレンドステートの作成
	this->CreateBlendState();
	// 深度ステンシルステートの作成
	this->CreateDepthStencilState();
	// ラスタライザーステートの作成
	this->CreateRasterizerState();

}

/// <summary>
/// デストラクタ
/// </summary>
SpriteMaterial::~SpriteMaterial()
{

}

/// <summary>
/// 頂点シェーダーをロード
/// </summary>
void SpriteMaterial::LoadVertexShader(const wchar_t* path , std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayout)
{
	std::vector<uint8_t> blob;
	// 頂点シェーダをロードする
	blob = DX::ReadData(path);
	DX::ThrowIfFailed(
		m_device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_vertexShader.ReleaseAndGetAddressOf())
	);
	//	インプットレイアウトの作成
	m_device->CreateInputLayout(&DEFAULT_INPUT_LAYOUT[0],
		static_cast<UINT>(DEFAULT_INPUT_LAYOUT.size()),
		blob.data(), blob.size(),
		m_inputLayout.GetAddressOf());
}
/// <summary>
/// ジオメトリシェーダーをロード
/// </summary>
void SpriteMaterial::LoadGeometryShader(const wchar_t* path)
{
	// ジオメトリシェーダをロードする
	std::vector<uint8_t> blob;
	blob = DX::ReadData(path);
	DX::ThrowIfFailed(
		m_device->CreateGeometryShader(blob.data(), blob.size(), nullptr, m_geometryShader.ReleaseAndGetAddressOf())
	);
}
/// <summary>
/// ピクセルシェーダーをロード
/// </summary>
void SpriteMaterial::LoadPixelShader(const wchar_t* path)
{
	// ピクセルシェーダをロードする
	std::vector<uint8_t> blob;
	blob = DX::ReadData(path);
	DX::ThrowIfFailed(
		m_device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_pixelShader.ReleaseAndGetAddressOf())
	);
}
/// <summary>
/// テクスチャをロードする
/// </summary>
void SpriteMaterial::LoadTexture(ID3D11ShaderResourceView* texture, int& width, int& height)
{
	// 画像をセット
	m_texture = texture;

	// 画像のサイズを取得する
	// 一時的な変数の宣言
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	D3D11_TEXTURE2D_DESC desc;

	// テクスチャの情報を取得する================================
	// テクスチャをID3D11Resourceとして見る
	m_texture->GetResource(resource.GetAddressOf());
	// ID3D11ResourceをID3D11Texture2Dとして見る
	resource.As(&texture2D);
	// テクスチャ情報を取得する
	texture2D->GetDesc(&desc);

	// テクスチャサイズを取得し、float型に変換する
	width = static_cast<int>(desc.Width);
	height = static_cast<int>(desc.Height);
}
/// <summary>
/// ルール画像をロードする
/// </summary>
void SpriteMaterial::LoadRuleTexture(ID3D11ShaderResourceView* texture)
{
	// ルール画像を取得する
	m_ruleTexture = texture;
}
/// <summary>
/// シェーダーの設定
/// </summary>
void SpriteMaterial::Begin()
{
	// 頂点バッファのデータを更新
	m_context->UpdateSubresource(m_vBuffer.Get(), 0, NULL, &m_vertexBuffer, 0, 0);
	
	// 定数バッファを設定する
	for (const auto& buffer : m_cBuffers)
	{
		// 定数バッファをシェーダーに設定
		ID3D11Buffer* cb[1] = { buffer.Get() };
		m_context->VSSetConstantBuffers(0, 1, cb);
		m_context->GSSetConstantBuffers(0, 1, cb);
		m_context->PSSetConstantBuffers(0, 1, cb);
	}
	
	// サンプラーステートをピクセルシェーダーに設定
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	m_context->PSSetSamplers(0, 1, sampler);

	// ブレンドステートを設定 (半透明描画用)
	m_context->OMSetBlendState(m_blendState.Get(), nullptr, 0xFFFFFFFF);
	// 深度ステンシルステートを設定 (深度バッファの書き込みと参照)
	//context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
	// ラスタライザーステートの設定
	m_context->RSSetState(m_rasterizerState.Get());
	// 入力レイアウトを設定
	m_context->IASetInputLayout(m_inputLayout.Get());

	// プリミティブトポロジーを設定 (ポイントリスト)
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// 頂点バッファを設定
	ID3D11Buffer* buffers[] = { m_vBuffer.Get() };
	UINT stride[] = { sizeof(VertexBuffer) };
	UINT offset[] = { 0 };
	m_context->IASetVertexBuffers(0, 1, buffers, stride, offset);

	// シェーダー登録
	m_context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	m_context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	m_context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	// ピクセルシェーダーにテクスチャリソースを設定
	m_context->PSSetShaderResources(0, 1, &m_texture);

	if(m_ruleTexture != nullptr)
		m_context->PSSetShaderResources(1, 1, &m_ruleTexture);
}
/// <summary>
/// シェーダーの解放
/// </summary>
void SpriteMaterial::End()
{
	// シェーダーの解放
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->GSSetShader(nullptr, nullptr, 0);
	m_context->PSSetShader(nullptr, nullptr, 0);
}

// ブレンドステートの作成
void SpriteMaterial::CreateBlendState()
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

	m_device->CreateBlendState(&blendDesc, &m_blendState);
}

// 深度ステンシルステートの作成
void SpriteMaterial::CreateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = TRUE;                          // 深度テストを有効化
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 深度バッファの書き込みを有効化
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;      // 深度テスト条件 (小さい場合のみ描画)
	depthStencilDesc.StencilEnable = FALSE;                       // ステンシルテストを無効化

	// 深度ステンシルステートを作成
	m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
}

// ラスタライザーステートの作成
void SpriteMaterial::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterDesc = {};
	rasterDesc.FillMode = D3D11_FILL_SOLID;      // 塗りつぶし (または D3D11_FILL_WIREFRAME)
	rasterDesc.CullMode = D3D11_CULL_NONE;       // カリングなし (または D3D11_CULL_FRONT / D3D11_CULL_BACK)
	rasterDesc.FrontCounterClockwise = FALSE;    // 時計回りの頂点順序を表面として認識
	rasterDesc.DepthClipEnable = TRUE;           // 深度クリッピングを有効化
	// ラスタライザーステートの作成
	m_device->CreateRasterizerState(&rasterDesc, &m_rasterizerState);
}