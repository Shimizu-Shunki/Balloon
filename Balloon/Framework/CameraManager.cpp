#include "Framework/pch.h"
#include "Framework/CameraManager.h"
#include "Framework/CommonResources.h"
#include "Interface/ICamera.h"

CameraManager::CameraManager()
{
	m_commonResources = CommonResources::GetInstance();
	m_cameraIndex = 0;
	m_isFadeActive = false;
	m_fadeTime = 0.0f;
}



void CameraManager::Attach(std::unique_ptr<ICamera> camera)
{
	// �J������ǉ�����
	m_cameras.push_back(std::move(camera));
}

void CameraManager::Update(const float& deltaTime)
{
	// �J������؂�ւ��鏈��
	this->Fade(deltaTime);

	// �J������؂�ւ��Ă��鎞�̓J�����̍X�V���X�g�b�v
	if (m_isFadeActive) return;

	// �J�����̍X�V����
	m_cameras[m_cameraIndex]->Update(deltaTime);
	// �r���[�s����쐬
	m_viewMatrix = m_cameras[m_cameraIndex]->CalculateViewMatrix();
}

void CameraManager::Detach()
{

}

void CameraManager::ChageCamera(int index)
{
	// �J������؂�ւ����ɂ���
	m_isFadeActive = true;

	// ���݂̃J�����̍��W����ۑ�
	m_currentPosition = m_cameras[m_cameraIndex]->GetPosition();
	// ���݂̃J�����̃^�[�Q�b�g���W����ۑ�
	m_currentTargetPosition = m_cameras[m_cameraIndex]->GetTargetPosition();

	// ���̃J�����̍��W����ۑ�
	m_nextPosition = m_cameras[index]->GetPosition();
	// ���̃J�����̃^�[�Q�b�g���W����ۑ�
	m_nextTargetPosition = m_cameras[index]->GetTargetPosition();

	// ���̃J�����̔ԍ���ݒ�
	m_cameraIndex = index;
	// �t�F�[�h�^�C�������Z�b�g
	m_fadeTime = 0.0f;
}

void CameraManager::Fade(const float& deltaTime)
{
	// �J�����؂�ւ����o�Ȃ���΍X�V���Ȃ�
	if (!m_isFadeActive) return;

	// �t�F�[�h���Ԃ��X�V����
	m_fadeTime += deltaTime;

	// ���݂̃J�����Ǝ��̃J�������Ԃ���
	DirectX::SimpleMath::Vector3 resultPosition = 
		DirectX::SimpleMath::Vector3::Lerp(m_currentPosition, m_nextPosition,m_fadeTime);
	// ���݂̃^�[�Q�b�g�Ǝ��̃^�[�Q�b�g���Ԃ���
	DirectX::SimpleMath::Vector3 resultTargetPosition =
		DirectX::SimpleMath::Vector3::Lerp(m_currentTargetPosition, m_nextTargetPosition, m_fadeTime);

	// �r���[�s����X�V����
	m_viewMatrix =
		DirectX::SimpleMath::Matrix::CreateLookAt(
			resultPosition, resultTargetPosition, DirectX::SimpleMath::Vector3::Up
	);

	if (m_fadeTime <= 1.0f) return;

	// �t�F�[�h���I��������A�N�e�B�u�ɂ���
	m_isFadeActive = false;
	// �t�F�[�h���I�������J�����̃r���[�s����쐬����
	m_viewMatrix = m_cameras[m_cameraIndex]->CalculateViewMatrix();


}