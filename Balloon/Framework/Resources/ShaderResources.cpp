#include "Framework/pch.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources.h"
#include <Framework/Microsoft/ReadData.h>
#include <unordered_map>
#include "Game/Material/PBRLit.h"


const std::vector<D3D11_INPUT_ELEMENT_DESC> ShaderResources::UI_INPUT_LAYOUT =
{
	// セマンティック名 インデックス フォーマット         入力スロット    オフセット                                                                                                                                         データ種別        インスタンスステップ率
		 { "SV_Position",0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  0,                                                                                                                                                         D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4 position
		 { "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  sizeof(DirectX::SimpleMath::Vector4),                                                                                                                      D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 rotate
		 { "TEXCOORD" ,  0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3),                                                                               D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 scale
		 { "TEXCOORD" ,  1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector3),                                        D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4 rect
		 { "COLOR",      0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 }  // float4 color
};
const std::vector<D3D11_INPUT_ELEMENT_DESC> ShaderResources::SEA_INPUT_LAYOUT =
{
	{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,                                    D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,    0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

ShaderResources::ShaderResources()
	:
	m_UIinputLayout{},
	m_UI_VS{},
	m_UI_GS{},
	m_UI_PS{},
	m_SeaInputLayout{},
	m_SeaVS{},
	m_SeaHS{},
	m_SeaDS{},
	m_SeaPS{},
	m_PBRLitInputLayout{},
	m_PBRLitVS{},
	m_PBRLitPS{},
	m_ShadowVS{},
	m_ShadowPS{},
	m_skyBoxVS{},
	m_skyBoxPS{}
{

}

void ShaderResources::LoadResource(const nlohmann::json& data)
{
	// デバイス
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// Shaderのパスを取得
	std::unordered_map<std::string, std::wstring> shaderPaths;
	if (data.contains("Shaders")) {
		for (const auto& entry : data["Shaders"]) {
			for (const auto& [key, value] : entry.items()) {
				shaderPaths[key] = Resources::ConvertToWString(value);
			}
		}
	}

	// シェーダー
	std::vector<uint8_t> blob;
	// 頂点シェーダをロードする
	blob = DX::ReadData(shaderPaths["UI_VS"].c_str());
	DX::ThrowIfFailed(
		device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_UI_VS.ReleaseAndGetAddressOf())
	);
	//	インプットレイアウトの作成
	device->CreateInputLayout(&UI_INPUT_LAYOUT[0],
		static_cast<UINT>(UI_INPUT_LAYOUT.size()),
		blob.data(), blob.size(),
		m_UIinputLayout.GetAddressOf());

	// ジオメトリシェーダをロードする
	blob = DX::ReadData(shaderPaths["UI_GS"].c_str());
	DX::ThrowIfFailed(
		device->CreateGeometryShader(blob.data(), blob.size(), nullptr, m_UI_GS.ReleaseAndGetAddressOf())
	);
	// ピクセルシェーダをロードする
	blob = DX::ReadData(shaderPaths["UI_PS"].c_str());
	DX::ThrowIfFailed(
		device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_UI_PS.ReleaseAndGetAddressOf())
	);

	// 頂点シェーダをロードする
	blob = DX::ReadData(shaderPaths["Sea_VS"].c_str());
	DX::ThrowIfFailed(
		device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_SeaVS.ReleaseAndGetAddressOf())
	);

	//	インプットレイアウトの作成
	device->CreateInputLayout(&SEA_INPUT_LAYOUT[0],
		static_cast<UINT>(SEA_INPUT_LAYOUT.size()),
		blob.data(), blob.size(),
		m_SeaInputLayout.GetAddressOf());

	// ハルシェーダーをロードする
	blob = DX::ReadData(shaderPaths["Sea_HS"].c_str());
	DX::ThrowIfFailed(
		device->CreateHullShader(blob.data(), blob.size(), nullptr, m_SeaHS.ReleaseAndGetAddressOf())
	);

	// ドメインシェーダをロードする
	blob = DX::ReadData(shaderPaths["Sea_DS"].c_str());
	DX::ThrowIfFailed(
		device->CreateDomainShader(blob.data(), blob.size(), nullptr, m_SeaDS.ReleaseAndGetAddressOf())
	);

	// ピクセルシェーダをロードする
	blob = DX::ReadData(shaderPaths["Sea_PS"].c_str());
	DX::ThrowIfFailed(
		device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_SeaPS.ReleaseAndGetAddressOf())
	);

	// シャドウマップ
	// 頂点シェーダをロードする
	blob = DX::ReadData(shaderPaths["ShadowMap_VS"].c_str());
	DX::ThrowIfFailed(
		device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_ShadowVS.ReleaseAndGetAddressOf())
	);
	// ピクセルシェーダをロードする
	blob = DX::ReadData(shaderPaths["ShadowMap_PS"].c_str());
	DX::ThrowIfFailed(
		device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_ShadowPS.ReleaseAndGetAddressOf())
	);

	// 物理ベースレンダリング
	// 頂点シェーダをロードする
	blob = DX::ReadData(shaderPaths["PBRLit_VS"].c_str());
	DX::ThrowIfFailed(
		device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_PBRLitVS.ReleaseAndGetAddressOf())
	);
	//	インプットレイアウトの作成
	device->CreateInputLayout(&DirectX::VertexPositionNormalTangentColorTexture::InputElements[0],
		static_cast<UINT>(DirectX::VertexPositionNormalTangentColorTexture::InputElementCount),
		blob.data(), blob.size(),
		m_PBRLitInputLayout.GetAddressOf());

	// ピクセルシェーダをロードする
	blob = DX::ReadData(shaderPaths["PBRLit_PS"].c_str());
	DX::ThrowIfFailed(
		device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_PBRLitPS.ReleaseAndGetAddressOf())
	);

	// スカイボックス
	// 頂点シェーダをロードする
	blob = DX::ReadData(shaderPaths["SkyBox_VS"].c_str());
	DX::ThrowIfFailed(
		device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_skyBoxVS.ReleaseAndGetAddressOf())
	);
	// ピクセルシェーダをロードする
	blob = DX::ReadData(shaderPaths["SkyBox_PS"].c_str());
	DX::ThrowIfFailed(
		device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_skyBoxPS.ReleaseAndGetAddressOf())
	);
}