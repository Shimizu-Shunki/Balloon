// ============================================
// 
// ファイル名: BalloonMaterial.cpp
// 概要: 風船のマテリアル
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Material/BalloonMaterial.h"
#include "Interface/IMaterial.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/ShaderResources.h"

/// <summary>
/// コンストラクタ
/// </summary>
BalloonMaterial::BalloonMaterial()
	:
	m_inputLayout{},
	m_context{},
	m_states{},
	m_vertexShader{},
	m_pixelShader{},
	m_PBRLitconstantBuffer{},
	m_constantBuffer{},
	m_baseMap{},
	m_normalMap{},
	m_skyMap{}
{

}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="resources">リソース</param>
void BalloonMaterial::Initialize(Resources* resources)
{
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	m_context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	m_states = CommonResources::GetInstance()->GetCommonStates();

	// 入力レイアウトを設定
	m_inputLayout = resources->GetShaderResources()->GetPBRLitInputLayout();

	// シェーダーを設定
	m_vertexShader = resources->GetShaderResources()->GetPBRLitVS();
	m_pixelShader  = resources->GetShaderResources()->GetBalloonPS();

	// 定数バッファ用のバッファオブジェクトを作成する
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(PBRLitConstantBuffer));	// 16の倍数を指定する
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	DX::ThrowIfFailed(
		device->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer.ReleaseAndGetAddressOf())
	);
}

/// <summary>
/// 定数バッファ更新処理
/// </summary>
void BalloonMaterial::UpdateConstBuffer()
{
	// GPUが使用するリソースのメモリにCPUからアクセスする際に利用する構造体
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	// コンテキスト
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// 定数バッファをマップする
	context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// 定数バッファに送るデータを準備する
	PBRLitConstantBuffer* cb = static_cast<PBRLitConstantBuffer*>(mappedResource.pData);
	cb->baseColor = m_PBRLitconstantBuffer.baseColor;
	cb->matallic = m_PBRLitconstantBuffer.matallic;
	cb->smoothness = m_PBRLitconstantBuffer.smoothness;
	cb->useBaseMap = m_PBRLitconstantBuffer.useBaseMap;
	cb->useNormalMap = m_PBRLitconstantBuffer.useNormalMap;
	// マップを解除する
	context->Unmap(m_constantBuffer.Get(), 0);
}

/// <summary>
/// マテリアルを適応する
/// </summary>
void BalloonMaterial::BeginMaterial()
{

	m_context->IASetInputLayout(m_inputLayout);

	// 定数バッファを指定する
	ID3D11Buffer* cbuf[] = { m_constantBuffer.Get() };
	m_context->VSSetConstantBuffers(2, 1, cbuf);
	m_context->PSSetConstantBuffers(2, 1, cbuf);

	// テクスチャの設定
	std::vector<ID3D11ShaderResourceView*> tex = {
		m_baseMap,
		m_baseMap,
		m_skyMap,
	};

	m_context->VSSetShaderResources(0, (UINT)tex.size(), tex.data());
	m_context->PSSetShaderResources(0, (UINT)tex.size(), tex.data());

	// シェーダーを設定
	m_context->VSSetShader(m_vertexShader, nullptr, 0);
	m_context->PSSetShader(m_pixelShader , nullptr, 0);

	// サンプラーステートを指定する
	ID3D11SamplerState* sampler[] = { m_states->LinearWrap() };
	m_context->VSSetSamplers(0, 1, sampler);
	m_context->PSSetSamplers(0, 1, sampler);
}

/// <summary>
/// マテリアルを解放
/// </summary>
void BalloonMaterial::EndMaterial()
{
	// シェーダの解放
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->PSSetShader(nullptr, nullptr, 0);
	// テクスチャリソースの解放
	m_context->PSSetShaderResources(0, 1, nullptr);
	m_context->PSSetShaderResources(1, 1, nullptr);
	m_context->PSSetShaderResources(2, 1, nullptr);
}