#pragma once
#include "Interface/ICamera.h"

class CommonResources;
class ICamera;


class CameraManager
{
public:

	// �r���[�s����擾����
	DirectX::SimpleMath::Matrix GetViewMatrix() const { return m_viewMatrix; }
	// �r���[�s���ݒ�
	void SetViewMatrix(DirectX::SimpleMath::Matrix viewMatrix) { m_viewMatrix = viewMatrix; }

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
	// �J�����̍X�V����
	void Update(const float& deltaTime);

	// �J������ǉ�
	void Attach(std::unique_ptr<ICamera> camera);
	// �J�������폜
	void Detach();

	// �J�����t�F�[�h����
	void Fade(const float& deltaTime);

	// �J������؂�ւ���
	void ChageCamera(int index);

private:
	// �O���t�B�b�N
	CommonResources* m_commonResources;

	// �Ǘ��Ώۂ̃J�������X�g
	std::vector<std::unique_ptr<ICamera>> m_cameras; 

	// ���݂̃J�����ԍ�
	int m_cameraIndex;

	// �J������؂�ւ������ǂ���
	bool m_isFadeActive;

	// ���݂̃J�����̍��W
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// ���݂̃J�����̃^�[�Q�b�g���W
	DirectX::SimpleMath::Vector3 m_currentTargetPosition;
	// ���̃J�����̍��W
	DirectX::SimpleMath::Vector3 m_nextPosition;
	// ���̃J�����̃^�[�Q�b�g���W
	DirectX::SimpleMath::Vector3 m_nextTargetPosition;

	// �t�F�[�h����
	float m_fadeTime;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_viewMatrix;


};