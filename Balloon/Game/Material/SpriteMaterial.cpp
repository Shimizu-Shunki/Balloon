#include "Framework/pch.h"
#include "Game/Material/SpriteMaterial.h"
#include <Framework/Microsoft/ReadData.h>

/// <summary>
/// コンストラクタ
/// </summary>
SpriteMaterial::SpriteMaterial(ID3D11Device1* device, ID3D11DeviceContext1* context)
	:
	m_device{},
	m_context{},
	m_vertexBuffer{},
	m_vBuffer{},
	m_cBuffers{},
	m_texture{},
	m_ruleTexture{},
	m_vertexShader{},
	m_geometryShader{},
	m_pixelShader{}
{
	m_device = device;
	m_context = context;

	m_ruleTexture = nullptr;

	
	// シェーダーにデータを渡すためのバーテックスバッファの作成
	D3D11_BUFFER_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(VertexBuffer);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	device->CreateBuffer(&desc, nullptr, &m_vBuffer);
}

/// <summary>
/// デストラクタ
/// </summary>
SpriteMaterial::~SpriteMaterial()
{

}


/// <summary>
/// テクスチャをロードする
/// </summary>
void SpriteMaterial::SetTexture(ID3D11ShaderResourceView* texture, int& width, int& height)
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
void SpriteMaterial::SetRuleTexture(ID3D11ShaderResourceView* texture)
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
	
	// 頂点バッファを設定
	ID3D11Buffer* buffers[] = { m_vBuffer.Get() };
	UINT stride[] = { sizeof(VertexBuffer) };
	UINT offset[] = { 0 };
	m_context->IASetVertexBuffers(0, 1, buffers, stride, offset);

	// シェーダー登録
	m_context->VSSetShader(m_vertexShader  , nullptr, 0);
	m_context->GSSetShader(m_geometryShader, nullptr, 0);
	m_context->PSSetShader(m_pixelShader   , nullptr, 0);

	// ピクセルシェーダーにテクスチャリソースを設定
	m_context->PSSetShaderResources(0, 1, &m_texture);
	// ピクセルシェーダーにルール画像を設定
	if (m_ruleTexture != nullptr)
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
