#include "Framework/pch.h"
#include "Game/Material/SpriteMaterial.h"
#include <Framework/Microsoft/ReadData.h>

/// <summary>
/// �C���v�b�g���C�A�E�g
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> SpriteMaterial::DEFAULT_INPUT_LAYOUT =
{
	// �Z�}���e�B�N�X��  �C���f�b�N�X    �t�H�[�}�b�g  ���̓X���b�g �I�t�Z�b�g  �f�[�^���  �C���X�^���X�X�e�b�v��
	{ "SV_Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0,                                                                                D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, sizeof(DirectX::SimpleMath::Vector4),                                             D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3),      D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",       0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3) + 
														   sizeof(DirectX::SimpleMath::Vector4),                                             D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3) +
														   sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector4),      D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
SpriteMaterial::SpriteMaterial(ID3D11Device1* device, ID3D11DeviceContext1* context)
{
	m_device = device;
	m_context = context;

		// �R�����X�e�[�g�̍쐬
	m_states = std::make_unique<DirectX::CommonStates>(m_device);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SpriteMaterial::~SpriteMaterial()
{

}

/// <summary>
/// ���_�V�F�[�_�[�����[�h
/// </summary>
void SpriteMaterial::LoadVertexShader(const wchar_t* path , std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayout)
{
	std::vector<uint8_t> blob;
	// ���_�V�F�[�_�����[�h����
	blob = DX::ReadData(path);
	DX::ThrowIfFailed(
		m_device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_vertexShader.ReleaseAndGetAddressOf())
	);
	//	�C���v�b�g���C�A�E�g�̍쐬
	m_device->CreateInputLayout(&inputLayout[0],
		static_cast<UINT>(inputLayout.size()),
		blob.data(), blob.size(),
		m_inputLayout.GetAddressOf());
}
/// <summary>
/// �W�I���g���V�F�[�_�[�����[�h
/// </summary>
void SpriteMaterial::LoadGeometryShader(const wchar_t* path)
{
	// �W�I���g���V�F�[�_�����[�h����
	std::vector<uint8_t> blob;
	blob = DX::ReadData(path);
	DX::ThrowIfFailed(
		m_device->CreateGeometryShader(blob.data(), blob.size(), nullptr, m_geometryShader.ReleaseAndGetAddressOf())
	);
}
/// <summary>
/// �s�N�Z���V�F�[�_�[�����[�h
/// </summary>
void SpriteMaterial::LoadPixelShader(const wchar_t* path)
{
	// �s�N�Z���V�F�[�_�����[�h����
	std::vector<uint8_t> blob;
	blob = DX::ReadData(path);
	DX::ThrowIfFailed(
		m_device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_pixelShader.ReleaseAndGetAddressOf())
	);
}
/// <summary>
/// �e�N�X�`�������[�h����
/// </summary>
void SpriteMaterial::LoadTexture(ID3D11ShaderResourceView* texture, int& width, int& height)
{
	// �摜���Z�b�g
	m_texture = texture;

	// �摜�̃T�C�Y���擾����
	// �ꎞ�I�ȕϐ��̐錾
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	D3D11_TEXTURE2D_DESC desc;

	// �e�N�X�`���̏����擾����================================
	// �e�N�X�`����ID3D11Resource�Ƃ��Č���
	m_texture->GetResource(resource.GetAddressOf());
	// ID3D11Resource��ID3D11Texture2D�Ƃ��Č���
	resource.As(&texture2D);
	// �e�N�X�`�������擾����
	texture2D->GetDesc(&desc);

	// �e�N�X�`���T�C�Y���擾���Afloat�^�ɕϊ�����
	width = static_cast<int>(desc.Width);
	height = static_cast<int>(desc.Height);
}
/// <summary>
/// ���[���摜�����[�h����
/// </summary>
void SpriteMaterial::LoadRuleTexture(ID3D11ShaderResourceView* texture)
{
	// ���[���摜���擾����
	m_ruleTexture = texture;
}
/// <summary>
/// �V�F�[�_�[�̐ݒ�
/// </summary>
void SpriteMaterial::Begin()
{
	// ���_�o�b�t�@�̃f�[�^���X�V
	m_context->UpdateSubresource(m_vBuffer.Get(), 0, NULL, &m_vertexBuffer, 0, 0);
	// �萔�o�b�t�@�̃f�[�^���X�V
	m_context->UpdateSubresource(m_cBuffer.Get(), 0, NULL, &m_constBuffer, 0, 0);

	// �萔�o�b�t�@���V�F�[�_�[�ɐݒ�
	ID3D11Buffer* cb[1] = { m_cBuffer.Get() };
	m_context->VSSetConstantBuffers(0, 1, cb);
	m_context->GSSetConstantBuffers(0, 1, cb);
	m_context->PSSetConstantBuffers(0, 1, cb);

	// �T���v���[�X�e�[�g���s�N�Z���V�F�[�_�[�ɐݒ�
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	m_context->PSSetSamplers(0, 1, sampler);

	// �u�����h�X�e�[�g��ݒ� (�������`��p)
	m_context->OMSetBlendState(m_blendState.Get(), nullptr, 0xFFFFFFFF);
	// �[�x�X�e���V���X�e�[�g��ݒ� (�[�x�o�b�t�@�̏������݂ƎQ��)
	//context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
	// ���X�^���C�U�[�X�e�[�g�̐ݒ�
	m_context->RSSetState(m_rasterizerState.Get());
	// ���̓��C�A�E�g��ݒ�
	m_context->IASetInputLayout(m_inputLayout.Get());

	// �v���~�e�B�u�g�|���W�[��ݒ� (�|�C���g���X�g)
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// ���_�o�b�t�@��ݒ�
	ID3D11Buffer* buffers[] = { m_vBuffer.Get() };
	UINT stride[] = { sizeof(VertexBuffer) };
	UINT offset[] = { 0 };
	m_context->IASetVertexBuffers(0, 1, buffers, stride, offset);

	// �V�F�[�_�[�o�^
	m_context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	m_context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	m_context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	// �s�N�Z���V�F�[�_�[�Ƀe�N�X�`�����\�[�X��ݒ�
	m_context->PSSetShaderResources(0, 1, &m_texture);
	m_context->PSSetShaderResources(1, 1, &m_ruleTexture);
}
/// <summary>
/// �V�F�[�_�[�̉��
/// </summary>
void SpriteMaterial::End()
{
	// �V�F�[�_�[�̉��
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->GSSetShader(nullptr, nullptr, 0);
	m_context->PSSetShader(nullptr, nullptr, 0);
}
