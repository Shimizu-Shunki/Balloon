#include "pch.h"
#include "Framework/Renderer.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include "Interface/IRenderableObject.h"
#include "Game/Particle/Particle.h"
#include "Game/Particle/ParticleEmitter.h"

Renderer::Renderer()
{
	m_commonResources = CommonResources::GetInstance();
	m_device          = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	m_context         = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	m_commonStates    = CommonResources::GetInstance()->GetCommonStates();


	m_particleConstBuffer = std::make_unique<ConstantBuffer<ParticleConstBuffer>>();
	m_particleConstBuffer->Initialize(m_commonResources->GetDeviceResources()->GetD3DDevice());

	// ���_�V�F�[�_�[���擾����
	m_vertexShader   = Resources::GetInstance()->GetShaderResources()->GetVertexShader(VS_ID::Particle_VS);
	// �W�I���g���V�F�[�_�[���擾����
	m_geometryShader = Resources::GetInstance()->GetShaderResources()->GetGeometryShader(GS_ID::Particle_GS);
	// �C���v�b�g���C�A�E�g���擾����
	m_inputLayout    = Resources::GetInstance()->GetShaderResources()->GetParticleInputLayout();

	// �V�F�[�_�[�Ƀf�[�^��n�����߂�UI�̃o�[�e�b�N�X�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	// �T�C�Y�͕K�v�Ȓ��_���ɂ���
	desc.ByteWidth = sizeof(DirectX::VertexPositionColorTexture) * 700; 
	// ���t���[������������Ȃ�DYNAMIC���g��
	desc.Usage = D3D11_USAGE_DYNAMIC;
	// �o�C���h�t���O��VertexBuffer
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// CPU���珑�����݂ł���悤�ɂ���
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	// �o�b�t�@�쐬
	m_device->CreateBuffer(&desc, nullptr, &m_vertexBuffer);
}


void Renderer::Render()
{
	DirectX::SimpleMath::Matrix viewMatrix       = m_commonResources->GetViewMatrix();
	DirectX::SimpleMath::Matrix projectionMatrix = m_commonResources->GetProjectionMatrix();

	// �I�u�W�F�N�g��`����s��
	for (const auto &object : m_renderableObjects)
	{
		if(object.first->GetIsActive() && object.second->GetIsActive())
		object.second->Render(m_context, m_commonStates, viewMatrix, projectionMatrix);
	}

	// �p�[�e�B�N���`��
	this->ParticleRender(viewMatrix, projectionMatrix);
}



void Renderer::Attach(IObject* object, IRenderableObject* renderableObject)
{
	m_renderableObjects[object] = renderableObject;
}


void Renderer::ParticleRender(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	ParticleConstBuffer particleConstBuffer = {};
	particleConstBuffer.projectionMatrix = projectionMatrix.Transpose();
	particleConstBuffer.viewMatrix = viewMatrix.Transpose();
	// �r���{�[�h�s������
	m_billboardMatrix = viewMatrix.Invert();
	m_billboardMatrix._41 = 0.0f;
	m_billboardMatrix._42 = 0.0f;
	m_billboardMatrix._43 = 0.0f;
	particleConstBuffer.billboardMatrix = m_billboardMatrix.Transpose();
	particleConstBuffer.worldMatrix = world.Transpose();
	particleConstBuffer.time = DirectX::SimpleMath::Vector4::Zero;

	// �萔�o�b�t�@�̍X�V
	m_particleConstBuffer->Update(m_context, particleConstBuffer);

	//	�V�F�[�_�[�ɒ萔�o�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_particleConstBuffer->GetBuffer() };
	m_context->VSSetConstantBuffers(0, 1, cb);
	m_context->GSSetConstantBuffers(0, 1, cb);
	m_context->PSSetConstantBuffers(0, 1, cb);

	//	�������`��w��		��ԃA���t�@����
	ID3D11BlendState* blendstate = m_commonStates->NonPremultiplied();
	//	�������菈��
	m_context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	m_context->OMSetDepthStencilState(m_commonStates->DepthRead(), 0);

	//	�J�����O�͂Ȃ�
	m_context->RSSetState(m_commonStates->CullNone());

	//	�C���v�b�g���C�A�E�g�̓o�^
	m_context->IASetInputLayout(m_inputLayout);

	// �v���~�e�B�u�g�|���W�[��ݒ�
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// ���_�V�F�[�_�[�̐ݒ�
	m_context->VSSetShader(m_vertexShader, nullptr, 0);
	// �W�I���g���V�F�[�_�[�̐ݒ�
	m_context->GSSetShader(m_geometryShader, nullptr, 0);

	for (const auto& particleEmitter : m_particleEmitter)
	{
		if (!particleEmitter->GetIsActive()) break;

		if (particleEmitter->GetInputDatas().size() <= 0) break;

		// ���[���h�s���ݒ�
		particleConstBuffer.worldMatrix = DirectX::SimpleMath::Matrix::Identity;

		// �萔�o�b�t�@�̍X�V
		m_particleConstBuffer->UpdateIfNeeded(m_context, particleConstBuffer);

		// �e�N�X�`���̐ݒ�
		ID3D11ShaderResourceView* srv = particleEmitter->GetTexture();
		m_context->PSSetShaderResources(0, 1, &srv);

		//	�摜�p�T���v���[�̓o�^
		ID3D11SamplerState* sampler[1] = { m_commonStates->LinearWrap() };
		m_context->PSSetSamplers(0, 1, sampler);

		// �s�N�Z���V�F�[�_�[�̐ݒ�
		m_context->PSSetShader(particleEmitter->GetPixelShader(), nullptr, 0);

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		m_context->Map(m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

		memcpy(mappedResource.pData, particleEmitter->GetInputDatas().data(),
			sizeof(DirectX::VertexPositionColorTexture) * particleEmitter->GetInputDatas().size());

		m_context->Unmap(m_vertexBuffer.Get(), 0);


		UINT stride = sizeof(DirectX::VertexPositionColorTexture);
		UINT offset = 0;
		ID3D11Buffer* buffer = m_vertexBuffer.Get();
		m_context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);

		// �`�揈��
		m_context->Draw(static_cast<UINT>(particleEmitter->GetInputDatas().size()), 0);

		// �s�N�Z���V�F�[�_�̉��
		m_context->PSSetShader(nullptr, nullptr, 0);

		// �e�N�X�`�����\�[�X�����
		ID3D11ShaderResourceView* nullsrv[] = { nullptr };
		m_context->PSSetShaderResources(0, 1, nullsrv);
	}

	//	�V�F�[�_�̓o�^���������Ă���
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->GSSetShader(nullptr, nullptr, 0);
}
