#include "Framework/pch.h"
#include "Framework/CameraManager.h"
#include "Framework/CommonResources.h"
#include "Interface/ICamera.h"
#include "Game/Transform/Transform.h"
#include "Framework/Tween/Tween.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CameraManager::CameraManager()
	:
	m_cameraIndex{},
	m_cameras{},
	m_pendingCameras{},
	m_viewMatrix{},
	m_projectionMatrix{},
	m_isFadeActive{},
	m_transform{}
{
	// ������
	m_cameraIndex  = 0;
	m_isFadeActive = false;
	// Transform�̍쐬
	m_transform = std::make_unique<Transform>();

	// �v���W�F�N�V�����s��쐬
	m_projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		DirectX::XMConvertToRadians(60.0f),
		SCREEN_W / SCREEN_H,
		0.1f,
		10000.0f
	);
}


/// <summary>
/// �J������ǉ�����
/// </summary>
/// <param name="camera">�ǉ�����J����</param>
ICamera* CameraManager::Attach(std::unique_ptr<ICamera> camera)
{
	// �J������ǉ�����
	m_pendingCameras.push_back(std::move(camera));

	// ���݂̃J������ݒ���s�����ߕԂ�
	return camera.get();

}
/// <summary>
/// �X�V����
/// </summary>
void CameraManager::Update()
{
	// �J������؂�ւ��鏈��
	this->Fade();

	// �J������؂�ւ��Ă��鎞�̓J�����̍X�V���X�g�b�v
	if (m_isFadeActive) return;

	// �J�����̍X�V����
	if (m_cameraIndex != -1)
	{
		m_cameras[m_cameraIndex]->Update();
		// �r���[�s����쐬
		//m_viewMatrix = m_cameras[m_cameraIndex]->CalculateViewMatrix();
		m_viewMatrix = m_cameras[m_cameraIndex]->GetViewMatrix();
	}
}

void CameraManager::Detach()
{

}

/// <summary>
/// �S�ẴJ�����������i�K�̂��̂ɐ؂�ւ���
/// </summary>
void CameraManager::SwitchCameras()
{
	// ���݂̃J�������폜
	m_cameras.clear();
	// �J�������X�V
	m_cameras = std::move(m_pendingCameras);
	// �����i�K�̔z����N���A����
	m_pendingCameras.clear();
	// �l��������
	if (m_cameras.size() == 0)
		m_cameraIndex = -1;
	else
		m_cameraIndex = 0;
}

/// <summary>
/// �w�肳�ꂽ�C���f�b�N�X�̃J�����ɐ؂�ւ���
/// </summary>
/// <param name="index">�؂�ւ���̃J�����̃C���f�b�N�X</param>
void CameraManager::SwitchActiveCamera(int index)
{
	// �J������؂�ւ����ɂ���
	m_isFadeActive = true;

	// ���݂̃J�����̍��W����ۑ�
	m_transform->SetLocalPosition(m_cameras[m_cameraIndex]->GetTransform()->GetLocalPosition());
	// ���݂̃J�����̃^�[�Q�b�g��ۑ�
	m_transform->SetLocalScale(m_cameras[m_cameraIndex]->GetTransform()->GetLocalScale());

	// Tween���N��
	m_transform->GetTween()->DOMove(m_cameras[index]->GetTransform()->GetLocalPosition(),0.0f);
	m_transform->GetTween()->DOScale(m_cameras[index]->GetTransform()->GetLocalScale(), 0.0f).OnComplete([this] {
		// �t�F�[�h���I�������J�����̃r���[�s����쐬����
		m_viewMatrix = m_cameras[m_cameraIndex]->CalculateViewMatrix();
	});

	// ���̃J�����̔ԍ���ݒ�
	m_cameraIndex = index;
}
/// <summary>
/// �w�肳�ꂽ�C���f�b�N�X�̃J�����Ƀt�F�[�h�t���Ő؂�ւ���
/// </summary>
/// <param name="index">�؂�ւ���̃J�����̃C���f�b�N�X</param>
/// <param name="fadeTime">�J�����؂�ւ��̃t�F�[�h���ԁi�b�j</param>
/// <param name="easingType">�t�F�[�h�A�j���[�V�����̃C�[�W���O�^�C�v</param>
void CameraManager::SwitchActiveCamera(int index, float fadeTime, Tween::EasingType easingType)
{
	// �J������؂�ւ����ɂ���
	m_isFadeActive = true;

	// ���݂̃J�����̍��W����ۑ�
	m_transform->SetLocalPosition(m_cameras[m_cameraIndex]->GetTransform()->GetLocalPosition());
	// ���݂̃J�����̃^�[�Q�b�g��ۑ�
	m_transform->SetLocalScale(m_cameras[m_cameraIndex]->GetTransform()->GetLocalScale());

	// Tween���N��
	m_transform->GetTween()->DOMove(m_cameras[index]->GetTransform()->GetLocalPosition(), fadeTime).SetEase(easingType);
	m_transform->GetTween()->DOScale(m_cameras[index]->GetTransform()->GetLocalScale(), fadeTime).SetEase(easingType)
		.OnComplete([this] {
		// �t�F�[�h���I�������J�����̃r���[�s����쐬����
		m_viewMatrix = m_cameras[m_cameraIndex]->CalculateViewMatrix();
		// �t�F�[�h���A�N�e�B�u�ɂ���
		m_isFadeActive = false;
		});

	// ���̃J�����̔ԍ���ݒ�
	m_cameraIndex = index;
}

/// <summary>
/// �t�F�[�h���̃r���[�s����쐬
/// </summary>
void CameraManager::Fade()
{
	// �J�����؂�ւ����o�Ȃ���΍X�V���Ȃ�
	if (!m_isFadeActive) return;

	// �r���[�s����X�V����
	m_viewMatrix =
		DirectX::SimpleMath::Matrix::CreateLookAt(
			m_transform->GetLocalPosition(), m_transform->GetLocalScale(), DirectX::SimpleMath::Vector3::Up
	);	
}