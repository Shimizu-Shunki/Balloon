// ============================================
// 
// �t�@�C����: DefaultUi.cpp
// �T�v: UI�̃}�e���A��
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Material/DefaultUi.h"
#include "Framework/CommonResources.h"
#include <Framework/Microsoft/ReadData.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
DefaultUi::DefaultUi()
	:
	m_device{},
	m_context{},
	m_pixelShader{}
{
	m_device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	m_context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �o�b�t�@�I�u�W�F�N�g���쐬����
	this->UiCreateBuffer();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DefaultUi::~DefaultUi()
{

}


/// <summary>
/// �e�N�X�`�������[�h����
/// </summary>




/// <summary>
/// �V�F�[�_�[�̐ݒ�
/// </summary>
void DefaultUi::BeginMaterial()
{
	// ���_�o�b�t�@�̃f�[�^���X�V
	//m_context->UpdateSubresource(m_vBuffer.Get(), 0, NULL, &m_vertexBuffer, 0, 0);

	// �f�t�H���g�̒萔�o�b�t�@��ݒ�
	ID3D11Buffer* cb[1] = { m_constBufferObject.Get() };
	m_context->VSSetConstantBuffers(0, 1, cb);
	m_context->GSSetConstantBuffers(0, 1, cb);
	m_context->PSSetConstantBuffers(0, 1, cb);
	
	// �V�F�[�_�[�o�^
	m_context->PSSetShader(m_pixelShader   , nullptr, 0);
}
/// <summary>
/// �V�F�[�_�[�̉��
/// </summary>
void DefaultUi::EndMaterial()
{
	// �V�F�[�_�[�̉��
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->GSSetShader(nullptr, nullptr, 0);
	m_context->PSSetShader(nullptr, nullptr, 0);
	// �e�N�X�`�����\�[�X�̉��
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
	// UI�̒萔�o�b�t�@���X�V����
	m_context->UpdateSubresource(m_constBufferObject.Get(), 0, NULL, &m_constBuffer, 0, 0);
}
