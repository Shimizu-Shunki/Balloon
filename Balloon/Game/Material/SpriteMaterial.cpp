#include "Framework/pch.h"
#include "Game/Material/SpriteMaterial.h"
#include <Framework/Microsoft/ReadData.h>

/// <summary>
/// �R���X�g���N�^
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

	
	// �V�F�[�_�[�Ƀf�[�^��n�����߂̃o�[�e�b�N�X�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(VertexBuffer);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	device->CreateBuffer(&desc, nullptr, &m_vBuffer);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SpriteMaterial::~SpriteMaterial()
{

}


/// <summary>
/// �e�N�X�`�������[�h����
/// </summary>
void SpriteMaterial::SetTexture(ID3D11ShaderResourceView* texture, int& width, int& height)
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
void SpriteMaterial::SetRuleTexture(ID3D11ShaderResourceView* texture)
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
	
	// �萔�o�b�t�@��ݒ肷��
	for (const auto& buffer : m_cBuffers)
	{
		// �萔�o�b�t�@���V�F�[�_�[�ɐݒ�
		ID3D11Buffer* cb[1] = { buffer.Get() };
		m_context->VSSetConstantBuffers(0, 1, cb);
		m_context->GSSetConstantBuffers(0, 1, cb);
		m_context->PSSetConstantBuffers(0, 1, cb);
	}
	
	// ���_�o�b�t�@��ݒ�
	ID3D11Buffer* buffers[] = { m_vBuffer.Get() };
	UINT stride[] = { sizeof(VertexBuffer) };
	UINT offset[] = { 0 };
	m_context->IASetVertexBuffers(0, 1, buffers, stride, offset);

	// �V�F�[�_�[�o�^
	m_context->VSSetShader(m_vertexShader  , nullptr, 0);
	m_context->GSSetShader(m_geometryShader, nullptr, 0);
	m_context->PSSetShader(m_pixelShader   , nullptr, 0);

	// �s�N�Z���V�F�[�_�[�Ƀe�N�X�`�����\�[�X��ݒ�
	m_context->PSSetShaderResources(0, 1, &m_texture);
	// �s�N�Z���V�F�[�_�[�Ƀ��[���摜��ݒ�
	if (m_ruleTexture != nullptr)
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
