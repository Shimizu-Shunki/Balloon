// ============================================
// 
// ファイル名: Image.cpp
// 概要: UI画像の描画・テクスチャ設定を行うクラス
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Image/Image.h"
#include "Game/Transform/Transform.h"
#include "Game/Material/Buffers.h"
#include "Interface/IMaterial.h"

/// <summary>
/// コンストラクタ
/// </summary>
Image::Image()
	:
	m_isActive{},
	m_material{},
	m_transform{},
	m_texture{},
	m_ruleTexture{}
{
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="isActive">アクティブ状態</param>
/// <param name="material">マテリアル</param>
/// <param name="transform">トランスフォーム</param>
void Image::Initialize(bool isActive, IMaterial* material, Transform* transform)
{
	// 初期化設定
	m_isActive = isActive;
	m_transform = transform;
	m_material = material;
	m_texture = nullptr;
	m_ruleTexture = nullptr;
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="context">コンテキスト</param>
/// <param name="vertexBuffer">頂点バッファ</param>
/// <returns>マテリアル</returns>
IMaterial* Image::Render(ID3D11DeviceContext1* context,ID3D11Buffer* vertexBuffer)
{
	UIVertexBuffer UiVertexBuffer;

	UiVertexBuffer.position = {
		m_transform->GetLocalPosition().x , m_transform->GetLocalPosition().y ,
		m_transform->GetLocalPosition().z , 1.0f
	};
	UiVertexBuffer.rotation = m_transform->GetLocalRotation().ToEuler();
	UiVertexBuffer.scale    = m_transform->GetLocalScale();
	UiVertexBuffer.rect     = m_transform->GetRect();
	UiVertexBuffer.color    = m_transform->GetColor();

	// 頂点バッファの更新
	context->UpdateSubresource(vertexBuffer, 0, NULL, &UiVertexBuffer, 0, 0);

	// 頂点バッファ設定
	ID3D11Buffer* buffers[] = { vertexBuffer };
	UINT stride[] = { sizeof(UIVertexBuffer) };
	UINT offset[] = { 0 };
	context->IASetVertexBuffers(0, 1, buffers, stride, offset);

	// マテリアルを適応
	m_material->BeginMaterial();

	context->PSSetShaderResources(0, 1, &m_texture);

	if (m_ruleTexture != nullptr) {
		context->PSSetShaderResources(1, 1, &m_ruleTexture);
	}



	return m_material;
}

/// <summary>
/// テクスチャを設定
/// </summary>
/// <param name="texture">テクスチャ</param>
/// <param name="width">縦</param>
/// <param name="height">横</param>
void Image::SetTexture(ID3D11ShaderResourceView* texture, int& width, int& height)
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