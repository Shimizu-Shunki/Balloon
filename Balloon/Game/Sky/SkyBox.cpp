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

	// �X�J�C�{�b�N�X�p���f���̍쐬
	m_skyboxModel = DirectX::GeometricPrimitive::CreateSphere(context, 2.0f, 3, false);

	// �V�F�[�_�[
	std::vector<uint8_t> blob;
	// ���_�V�F�[�_�����[�h����
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\SkyBox_VS.cso");
	DX::ThrowIfFailed(
		device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_skyVertexShader.ReleaseAndGetAddressOf())
	);

	// �s�N�Z���V�F�[�_�����[�h����
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\SkyBox_PS.cso");
	DX::ThrowIfFailed(
		device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_skyPixelShader.ReleaseAndGetAddressOf())
	);

	// �X�J�C�}�b�v
	DirectX::CreateDDSTextureFromFile(
		device, L"Resources\\Textures\\DDS\\CubeMap.dds", nullptr, m_cubemap.ReleaseAndGetAddressOf());

	// �萔�o�b�t�@�p�̃o�b�t�@�I�u�W�F�N�g���쐬����
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(MatricesConstBuffer));	// 16�̔{�����w�肷��
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

	// ���[���h�s��̍쐬
	DirectX::SimpleMath::Matrix world =
		DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(angle * 0.01f));

	// GPU���g�p���郊�\�[�X�̃�������CPU����A�N�Z�X����ۂɗ��p����\����
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	// �R���e�L�X�g
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �萔�o�b�t�@���}�b�v����
	context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// �萔�o�b�t�@�ɑ���f�[�^����������
	MatricesConstBuffer* cb = static_cast<MatricesConstBuffer*>(mappedResource.pData);
	cb->worldMatrix = world.Transpose();
	cb->viewMatrix = view.Transpose();
	cb->projectionMatrix = projection.Transpose();
	// �}�b�v����������
	context->Unmap(m_constantBuffer.Get(), 0);
}

void SkyBox::Render(ID3D11DeviceContext1* context, DirectX::CommonStates* states)
{
	// �X�J�C�{�b�N�X�̕`��
	m_skyboxModel->Draw({}, {}, {}, {}, nullptr, false, [&]()
		{
			// �V�F�[�_�[�̐ݒ�
			context->VSSetShader(m_skyVertexShader.Get(), nullptr, 0);
			context->PSSetShader(m_skyPixelShader.Get() , nullptr, 0);

			// �萔�o�b�t�@�̐ݒ�i���ʒ萔�o�b�t�@�̂݁j
			context->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
			context->PSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());

			// �e�N�X�`���̐ݒ�
			context->VSSetShaderResources(0, 1, m_cubemap.GetAddressOf());
			context->PSSetShaderResources(0, 1, m_cubemap.GetAddressOf());
			// �T���v���[�̐ݒ�
			auto sampler = states->LinearClamp();
			context->VSSetSamplers(0, 1, &sampler);
			context->PSSetSamplers(0, 1, &sampler);
		});
}