#include "Framework/pch.h"
#include "Game/Material/SpriteMaterial.h"
#include <Framework/Microsoft/ReadData.h>

/// <summary>
/// インプットレイアウト
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> SpriteMaterial::DEFAULT_INPUT_LAYOUT =
{
	// セマンティクス名  インデックス    フォーマット  入力スロット オフセット  データ種別  インスタンスステップ率
	{ "SV_Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,                                                                                D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, sizeof(DirectX::SimpleMath::Vector4),                                             D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3),      D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",       0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3) + 
														   sizeof(DirectX::SimpleMath::Vector4),                                             D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3) +
														   sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector4),      D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

/// <summary>
/// コンストラクタ
/// </summary>
SpriteMaterial::SpriteMaterial(ID3D11Device1* device, ID3D11DeviceContext1* context)
{
	m_device = device;
	m_context = context;

		// コモンステートの作成
	m_states = std::make_unique<DirectX::CommonStates>(m_device);
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
	m_device->CreateInputLayout(&inputLayout[0],
		static_cast<UINT>(inputLayout.size()),
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
	// 定数バッファのデータを更新
	m_context->UpdateSubresource(m_cBuffer.Get(), 0, NULL, &m_constBuffer, 0, 0);

	// 定数バッファをシェーダーに設定
	ID3D11Buffer* cb[1] = { m_cBuffer.Get() };
	m_context->VSSetConstantBuffers(0, 1, cb);
	m_context->GSSetConstantBuffers(0, 1, cb);
	m_context->PSSetConstantBuffers(0, 1, cb);

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
