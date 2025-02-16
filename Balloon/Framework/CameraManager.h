#pragma once
#include "Interface/ICamera.h"
#include "Framework/Tween/Tween.h"

class ICamera;
class Transform;


class CameraManager
{
private:
	const float SCREEN_W = 1280.0f;
	const float SCREEN_H = 720.0f;

public:

	// �r���[�s����擾����
	DirectX::SimpleMath::Matrix GetViewMatrix() const { return m_viewMatrix; }
	// �r���[�s���ݒ�
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& viewMatrix) { m_viewMatrix = viewMatrix; }

	// �v���W�F�N�V�����s����擾����
	DirectX::SimpleMath::Matrix GetProjectionMatrix() const { return m_projectionMatrix; }
	// �v���W�F�N�V�����s���ݒ肷��
	void SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projectionMatirx) { m_projectionMatrix = projectionMatirx; }

private:
	//	�R���X�g���N�^
	CameraManager();
	//	�f�X�g���N�^
	~CameraManager() = default;

public:
	CameraManager(const CameraManager&) = delete;             // �R�s�[�֎~
	CameraManager& operator=(const CameraManager&) = delete;  // �R�s�[����֎~
	CameraManager(const CameraManager&&) = delete;            // ���[�u�֎~
	CameraManager& operator=(const CameraManager&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static CameraManager* GetInstance()
	{
		static CameraManager instance;
		return &instance;
	}

public:
	
	// ���݂̃J�������폜���A�����ς݂̃J�����ɐ؂�ւ���
	void SwitchCameras();
	// �J�����̍X�V����
	void Update();

	// �J������ǉ�
	ICamera* Attach(std::unique_ptr<ICamera> camera);
	// �J�������폜
	void Detach();

	// �J�����t�F�[�h����
	void Fade();

	// �J������؂�ւ���
	void SwitchActiveCamera(int index);
	void SwitchActiveCamera(int index, float fadeTime , Tween::EasingType easingType);

	

private:
	// ���݂̃J�����ԍ�
	int m_cameraIndex;

	// �Ǘ��Ώۂ̃J�������X�g
	std::vector<std::unique_ptr<ICamera>> m_cameras; 
	// �����i�K�̃J�������X�g
	std::vector<std::unique_ptr<ICamera>> m_pendingCameras;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_viewMatrix;
	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_projectionMatrix;

	// �J������؂�ւ������ǂ���
	bool m_isFadeActive;	
	
	// ���zTransform�i��ԗp�j
	std::unique_ptr<Transform> m_transform;	
};