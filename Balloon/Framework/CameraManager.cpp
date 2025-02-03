#include "Framework/pch.h"
#include "Framework/CameraManager.h"
#include "Framework/CommonResources.h"
#include "Interface/ICamera.h"
#include "Game/Transform/Transform.h"
#include "Framework/Tween/Tween.h"

CameraManager::CameraManager()
{
	m_commonResources = CommonResources::GetInstance();
	m_cameraIndex = 0;
	m_isFadeActive = false;
	m_fadeTime = 0.0f;

	m_transform = std::make_unique<Transform>();

}



void CameraManager::Attach(std::unique_ptr<ICamera> camera)
{
	// �J������ǉ�����
	m_cameras.push_back(std::move(camera));
}

void CameraManager::Update()
{
	// �J������؂�ւ��鏈��
	this->Fade();

	// �J������؂�ւ��Ă��鎞�̓J�����̍X�V���X�g�b�v
	if (m_isFadeActive) return;

	// �J�����̍X�V����
	//if (m_cameras[m_cameraIndex] != nullptr)
	//{
	//	m_cameras[m_cameraIndex]->Update();
	//	// �r���[�s����쐬
	//	m_viewMatrix = m_cameras[m_cameraIndex]->CalculateViewMatrix();
	//}
}

void CameraManager::Detach()
{

}

void CameraManager::ChageCamera(int index)
{
	// �J������؂�ւ����ɂ���
	m_isFadeActive = true;

	// ���݂̃J�����̍��W����ۑ�
	m_transform->SetLocalPosition(m_cameras[m_cameraIndex]->GetTransform()->GetLocalPosition());
	// ���݂̃J�����̃^�[�Q�b�g��ۑ�
	m_transform->SetLocalScale(m_cameras[m_cameraIndex]->GetTransform()->GetLocalScale());

	// Tween���N��
	m_transform->GetTween()->DOMove(m_cameras[index]->GetTransform()->GetLocalPosition(), 2.0f);
	m_transform->GetTween()->DOScale(m_cameras[index]->GetTransform()->GetLocalScale(), 2.0f).OnComplete([this] {
		// �t�F�[�h���I�������J�����̃r���[�s����쐬����
		m_viewMatrix = m_cameras[m_cameraIndex]->CalculateViewMatrix();
	});

	// ���̃J�����̔ԍ���ݒ�
	m_cameraIndex = index;
	// �t�F�[�h�^�C�������Z�b�g
	m_fadeTime = 0.0f;
}

void CameraManager::Fade()
{
	// �J�����؂�ւ����o�Ȃ���΍X�V���Ȃ�
	if (!m_isFadeActive) return;

	// �r���[�s����X�V����
	m_viewMatrix =
		DirectX::SimpleMath::Matrix::CreateLookAt(
			m_transform->GetLocalPosition(), m_transform->GetLocalScale(), DirectX::SimpleMath::Vector3::Up
	);	

	m_commonResources->GetCameraManager()->SetViewMatrix(m_viewMatrix);
}