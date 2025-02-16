#include "Framework/pch.h"
#include "Framework/RenderManager.h"
#include "Framework/CommonResources.h"
#include "Framework/CameraManager.h"
#include "Game/Transform/Transform.h"

RenderManager::RenderManager()
	:
	m_sprite{},
	m_pendingSprite{},
	m_skySphere{},
	m_renderableObjects{},
	m_pendingRenderableObjects{}
{
	// ���L���\�[�X
	auto commonResources = CommonResources::GetInstance();
	// �f�o�C�X
	m_device = commonResources->GetDeviceResources()->GetD3DDevice();
	// �R���e�L�X�g
	m_context = commonResources->GetDeviceResources()->GetD3DDeviceContext();
	// �R�����X�e�[�g
	m_commonStates = commonResources->GetCommonStates();
	// �J�����Ǘ��N���X
	m_cameraManager = commonResources->GetCameraManager();
}


void RenderManager::SwitchRenderbleObjects()
{
	// ���݂̃I�u�W�F�N�g���폜����
	m_renderableObjects.clear();
	// ���̃I�u�W�F�N�g���i�[����
	m_renderableObjects = m_pendingRenderableObjects;

	// ���݂̃X�v���C�g���폜����
	m_sprite.clear();
	// ���̃X�v���C�g���i�[����
	m_sprite = m_pendingSprite;

	m_pendingSprite.clear();
	m_pendingRenderableObjects.clear();
}

void RenderManager::Render()
{
	// �X�J�C�X�t�B�A��`�悷�� �X�J�C�X�t�B�A���Ȃ��ꍇ�G���[�������s���`����s��Ȃ�
	if (!m_skySphere.model) {
		throw std::runtime_error("m_skySphere.model is nullptr!");
	}

	// �v���W�F�N�V�����s����擾����
	const DirectX::SimpleMath::Matrix& projectionMatrix = m_cameraManager->GetProjectionMatrix();
	// �r���[�s����擾����
	const DirectX::SimpleMath::Matrix& viewMatrix       = m_cameraManager->GetViewMatrix();


	// ���f���̃G�t�F�N�g�����X�V����
	m_skySphere.model->UpdateEffects([](DirectX::IEffect* effect)
	{
		// �x�[�V�b�N�G�t�F�N�g��ݒ肷��
		DirectX::DX11::BasicEffect* basicEffect = dynamic_cast<DirectX::DX11::BasicEffect*>(effect);
		if (basicEffect)
		{
			// �ʂ̃��C�g�����ׂĖ���������
			basicEffect->SetLightEnabled(0, false);
			basicEffect->SetLightEnabled(1, false);
			basicEffect->SetLightEnabled(2, false);

			// ���f����������������
			basicEffect->SetEmissiveColor(DirectX::Colors::White);
		}
	});
	// �X�J�C�X�t�B�A��`�悷��
	m_skySphere.model->Draw(m_context, *m_commonStates, m_skySphere.transform->GetWorldMatrix(),
		viewMatrix, projectionMatrix);


	// ���f���̕`��
	for (const auto& model : m_renderableObjects)
	{
		if(model.model != nullptr)
		model.model->Draw(m_context, *m_commonStates, model.transform->GetWorldMatrix(),
			viewMatrix, projectionMatrix
		);
	}

	// �X�v���C�g�̕`��
	for (const auto& sprite : m_sprite)
	{
		if (sprite != nullptr)
		{
			// �}�e���A���̓K��
			sprite->Begin();
			// �`��
			m_context->Draw(1, 0);
			// �}�e���A���̉��
			sprite->End();
		}
	}
}