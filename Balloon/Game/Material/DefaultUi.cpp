// ============================================
// 
// ファイル名: DefaultUi.cpp
// 概要: UIのマテリアル
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Material/DefaultUi.h"
#include "Framework/CommonResources.h"
#include <Framework/Microsoft/ReadData.h>

/// <summary>
/// コンストラクタ
/// </summary>
DefaultUi::DefaultUi()
	:
	m_device{},
	m_context{},
	m_pixelShader{}
{
	m_device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	m_context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// バッファオブジェクトを作成する
	this->UiCreateBuffer();
}

/// <summary>
/// デストラクタ
/// </summary>
DefaultUi::~DefaultUi()
{

}


/// <summary>
/// テクスチャをロードする
/// </summary>




/// <summary>
/// シェーダーの設定
/// </summary>
void DefaultUi::BeginMaterial()
{
	// 頂点バッファのデータを更新
	//m_context->UpdateSubresource(m_vBuffer.Get(), 0, NULL, &m_vertexBuffer, 0, 0);

	// デフォルトの定数バッファを設定
	ID3D11Buffer* cb[1] = { m_constBufferObject.Get() };
	m_context->VSSetConstantBuffers(0, 1, cb);
	m_context->GSSetConstantBuffers(0, 1, cb);
	m_context->PSSetConstantBuffers(0, 1, cb);
	
	// シェーダー登録
	m_context->PSSetShader(m_pixelShader   , nullptr, 0);
}
/// <summary>
/// シェーダーの解放
/// </summary>
void DefaultUi::EndMaterial()
{
	// シェーダーの解放
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->GSSetShader(nullptr, nullptr, 0);
	m_context->PSSetShader(nullptr, nullptr, 0);
	// テクスチャリソースの解放
	ID3D11ShaderResourceView* nullsrv[] = { nullptr };
	m_context->PSSetShaderResources(0, 1, nullsrv);
	m_context->PSSetShaderResources(1, 1, nullsrv);
}


void DefaultUi::UiCreateBuffer()
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage     = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(UIConstBuffer);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	m_device->CreateBuffer(&bufferDesc, nullptr, m_constBufferObject.GetAddressOf());
}

void DefaultUi::UpdateConstBuffer()
{
	// UIの定数バッファを更新する
	m_context->UpdateSubresource(m_constBufferObject.Get(), 0, NULL, &m_constBuffer, 0, 0);
}
