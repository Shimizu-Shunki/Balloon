#include "Framework/pch.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources.h"
#include <Framework/Microsoft/ReadData.h>
#include <unordered_map>
#include "Game/Material/PBRLit.h"


const std::vector<D3D11_INPUT_ELEMENT_DESC> ShaderResources::UI_INPUT_LAYOUT =
{
	// �Z�}���e�B�b�N�� �C���f�b�N�X �t�H�[�}�b�g         ���̓X���b�g    �I�t�Z�b�g                                                                                                                                         �f�[�^���        �C���X�^���X�X�e�b�v��
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
	// �f�o�C�X
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// Shader�̃p�X���擾
	std::unordered_map<std::string, std::wstring> shaderPaths;
	if (data.contains("Shaders")) {
		for (const auto& entry : data["Shaders"]) {
			for (const auto& [key, value] : entry.items()) {
				shaderPaths[key] = Resources::ConvertToWString(value);
			}
		}
	}

	// �V�F�[�_�[
	std::vector<uint8_t> blob;
	// ���_�V�F�[�_�����[�h����
	blob = DX::ReadData(shaderPaths["UI_VS"].c_str());
	DX::ThrowIfFailed(
		device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_UI_VS.ReleaseAndGetAddressOf())
	);
	//	�C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(&UI_INPUT_LAYOUT[0],
		static_cast<UINT>(UI_INPUT_LAYOUT.size()),
		blob.data(), blob.size(),
		m_UIinputLayout.GetAddressOf());

	// �W�I���g���V�F�[�_�����[�h����
	blob = DX::ReadData(shaderPaths["UI_GS"].c_str());
	DX::ThrowIfFailed(
		device->CreateGeometryShader(blob.data(), blob.size(), nullptr, m_UI_GS.ReleaseAndGetAddressOf())
	);
	// �s�N�Z���V�F�[�_�����[�h����
	blob = DX::ReadData(shaderPaths["UI_PS"].c_str());
	DX::ThrowIfFailed(
		device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_UI_PS.ReleaseAndGetAddressOf())
	);

	// ���_�V�F�[�_�����[�h����
	blob = DX::ReadData(shaderPaths["Sea_VS"].c_str());
	DX::ThrowIfFailed(
		device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_SeaVS.ReleaseAndGetAddressOf())
	);

	//	�C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(&SEA_INPUT_LAYOUT[0],
		static_cast<UINT>(SEA_INPUT_LAYOUT.size()),
		blob.data(), blob.size(),
		m_SeaInputLayout.GetAddressOf());

	// �n���V�F�[�_�[�����[�h����
	blob = DX::ReadData(shaderPaths["Sea_HS"].c_str());
	DX::ThrowIfFailed(
		device->CreateHullShader(blob.data(), blob.size(), nullptr, m_SeaHS.ReleaseAndGetAddressOf())
	);

	// �h���C���V�F�[�_�����[�h����
	blob = DX::ReadData(shaderPaths["Sea_DS"].c_str());
	DX::ThrowIfFailed(
		device->CreateDomainShader(blob.data(), blob.size(), nullptr, m_SeaDS.ReleaseAndGetAddressOf())
	);

	// �s�N�Z���V�F�[�_�����[�h����
	blob = DX::ReadData(shaderPaths["Sea_PS"].c_str());
	DX::ThrowIfFailed(
		device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_SeaPS.ReleaseAndGetAddressOf())
	);

	// �V���h�E�}�b�v
	// ���_�V�F�[�_�����[�h����
	blob = DX::ReadData(shaderPaths["ShadowMap_VS"].c_str());
	DX::ThrowIfFailed(
		device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_ShadowVS.ReleaseAndGetAddressOf())
	);
	// �s�N�Z���V�F�[�_�����[�h����
	blob = DX::ReadData(shaderPaths["ShadowMap_PS"].c_str());
	DX::ThrowIfFailed(
		device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_ShadowPS.ReleaseAndGetAddressOf())
	);

	// �����x�[�X�����_�����O
	// ���_�V�F�[�_�����[�h����
	blob = DX::ReadData(shaderPaths["PBRLit_VS"].c_str());
	DX::ThrowIfFailed(
		device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_PBRLitVS.ReleaseAndGetAddressOf())
	);
	//	�C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(&DirectX::VertexPositionNormalTangentColorTexture::InputElements[0],
		static_cast<UINT>(DirectX::VertexPositionNormalTangentColorTexture::InputElementCount),
		blob.data(), blob.size(),
		m_PBRLitInputLayout.GetAddressOf());

	// �s�N�Z���V�F�[�_�����[�h����
	blob = DX::ReadData(shaderPaths["PBRLit_PS"].c_str());
	DX::ThrowIfFailed(
		device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_PBRLitPS.ReleaseAndGetAddressOf())
	);

	// �X�J�C�{�b�N�X
	// ���_�V�F�[�_�����[�h����
	blob = DX::ReadData(shaderPaths["SkyBox_VS"].c_str());
	DX::ThrowIfFailed(
		device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_skyBoxVS.ReleaseAndGetAddressOf())
	);
	// �s�N�Z���V�F�[�_�����[�h����
	blob = DX::ReadData(shaderPaths["SkyBox_PS"].c_str());
	DX::ThrowIfFailed(
		device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_skyBoxPS.ReleaseAndGetAddressOf())
	);
}