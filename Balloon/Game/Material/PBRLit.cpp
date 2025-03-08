#include "Framework/pch.h"
#include "Game/Material/PBRLit.h"
#include "Interface/IMaterial.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/ShaderResources.h"


PBRLit::PBRLit()
{

}

void PBRLit::Initialize(Resources* resources)
{
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	m_context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	m_states = CommonResources::GetInstance()->GetCommonStates();

	// ���̓��C�A�E�g��ݒ�
	m_inputLayout = resources->GetShaderResources()->GetPBRLitInputLayout();

	// �V�F�[�_�[��ݒ�
	m_vertexShader = resources->GetShaderResources()->GetPBRLitVS();
	m_pixelShader  = resources->GetShaderResources()->GetPBRLitPS();

	// �萔�o�b�t�@�p�̃o�b�t�@�I�u�W�F�N�g���쐬����
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(PBRLitConstantBuffer));	// 16�̔{�����w�肷��
	bufferDesc.Usage          = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	DX::ThrowIfFailed(
		device->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer.ReleaseAndGetAddressOf())
	);
}

void PBRLit::UpdateConstantBuffer()
{
	// GPU���g�p���郊�\�[�X�̃�������CPU����A�N�Z�X����ۂɗ��p����\����
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	// �R���e�L�X�g
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �萔�o�b�t�@���}�b�v����
	context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// �萔�o�b�t�@�ɑ���f�[�^����������
	PBRLitConstantBuffer* cb = static_cast<PBRLitConstantBuffer*>(mappedResource.pData);
	cb->baseColor = m_PBRLitconstantBuffer.baseColor;
	cb->matallic = m_PBRLitconstantBuffer.matallic;
	cb->smoothness = m_PBRLitconstantBuffer.smoothness;
	cb->useBaseMap = m_PBRLitconstantBuffer.useBaseMap;
	cb->useNormalMap = m_PBRLitconstantBuffer.useNormalMap;
	// �}�b�v����������
	context->Unmap(m_constantBuffer.Get(), 0);
}

void PBRLit::SetMaterial()
{

	m_context->IASetInputLayout(m_inputLayout);

	// �萔�o�b�t�@���w�肷��
	ID3D11Buffer* cbuf[] = { m_constantBuffer.Get() };
	m_context->VSSetConstantBuffers(2, 1, cbuf);
	m_context->PSSetConstantBuffers(2, 1, cbuf);

	// �e�N�X�`���̐ݒ�
	std::vector<ID3D11ShaderResourceView*> tex = {
		m_baseMap,
		m_normalMap,
		m_skyMap,
	};

	m_context->VSSetShaderResources(0, (UINT)tex.size(), tex.data());
	m_context->PSSetShaderResources(0, (UINT)tex.size(), tex.data());

	// �V�F�[�_�[��ݒ�
	m_context->VSSetShader(m_vertexShader, nullptr, 0);
	m_context->PSSetShader(m_pixelShader , nullptr, 0);

	// �T���v���[�X�e�[�g���w�肷��
	ID3D11SamplerState* sampler[] = { m_states->LinearWrap() };
	m_context->VSSetSamplers(0, 1, sampler);
	m_context->PSSetSamplers(0, 1, sampler);
}