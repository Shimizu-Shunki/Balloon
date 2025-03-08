#include "Framework/pch.h"
#include "Game/Sky/SkyBox.h"

#include "Framework/CommonResources.h"
#include <Framework/Microsoft/ReadData.h>

SkyBox::SkyBox()
{

}

void SkyBox::Initialize()
{
	ID3D11DeviceContext* context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// スカイボックス用モデルの作成
	m_skyboxModel = DirectX::GeometricPrimitive::CreateSphere(context, 2.0f, 3, false);

	// シェーダー
	std::vector<uint8_t> blob;
	// 頂点シェーダをロードする
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\SkyBox_VS.cso");
	DX::ThrowIfFailed(
		device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_skyVertexShader.ReleaseAndGetAddressOf())
	);

	// ピクセルシェーダをロードする
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\SkyBox_PS.cso");
	DX::ThrowIfFailed(
		device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_skyPixelShader.ReleaseAndGetAddressOf())
	);

	// スカイマップ
	DirectX::CreateDDSTextureFromFile(
		device, L"Resources\\Textures\\DDS\\CubeMap.dds", nullptr, m_cubemap.ReleaseAndGetAddressOf());

	// 定数バッファ用のバッファオブジェクトを作成する
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(MatricesConstBuffer));	// 16の倍数を指定する
	bufferDesc.Usage          = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	DX::ThrowIfFailed(
		device->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer.ReleaseAndGetAddressOf())
	);

	angle = 0.0f;
}

void SkyBox::Update(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	angle++;

	// ワールド行列の作成
	DirectX::SimpleMath::Matrix world =
		DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(angle * 0.01f));

	// GPUが使用するリソースのメモリにCPUからアクセスする際に利用する構造体
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	// コンテキスト
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// 定数バッファをマップする
	context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// 定数バッファに送るデータを準備する
	MatricesConstBuffer* cb = static_cast<MatricesConstBuffer*>(mappedResource.pData);
	cb->worldMatrix = world.Transpose();
	cb->viewMatrix = view.Transpose();
	cb->projectionMatrix = projection.Transpose();
	// マップを解除する
	context->Unmap(m_constantBuffer.Get(), 0);
}

void SkyBox::Render(ID3D11DeviceContext1* context, DirectX::CommonStates* states)
{
	// スカイボックスの描画
	m_skyboxModel->Draw({}, {}, {}, {}, nullptr, false, [&]()
		{
			// シェーダーの設定
			context->VSSetShader(m_skyVertexShader.Get(), nullptr, 0);
			context->PSSetShader(m_skyPixelShader.Get() , nullptr, 0);

			// 定数バッファの設定（共通定数バッファのみ）
			context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
			context->PSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());

			// テクスチャの設定
			context->VSSetShaderResources(0, 1, m_cubemap.GetAddressOf());
			context->PSSetShaderResources(0, 1, m_cubemap.GetAddressOf());
			// サンプラーの設定
			auto sampler = states->LinearClamp();
			context->VSSetSamplers(0, 1, &sampler);
			context->PSSetSamplers(0, 1, &sampler);
		});
}