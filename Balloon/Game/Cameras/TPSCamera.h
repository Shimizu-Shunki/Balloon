#pragma once
#include "Framework/CommonResources.h"
#include "Interface/ICamera.h"


class InputManager;
class IObject;
class Transform;

class TPSCamera : public ICamera
{

public :
	// SET
	// Transform���擾����
	Transform* GetTransform() const override { return m_transform.get(); }

public:
	// �r���[�s���ݒ肷��
	DirectX::SimpleMath::Matrix CalculateViewMatrix() override;
public :
	// �R���X�g���N�^
	TPSCamera(IObject* object);
	// �f�X�g���N�^
	~TPSCamera();

	
	// ����������
	void Initialize(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& targetPosition,
		const DirectX::SimpleMath::Quaternion& rotation, CameraManager* cameraManager);
	// �X�V����
	void Update();


private:

	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// �C���v�b�g�}�l�[�W���[
	InputManager* m_inputManager;
	// �ǐՂ���I�u�W�F�N�g
	IObject* m_targetObject;

	std::unique_ptr<Transform> m_transform;

	// �J�����}�l�[�W���[
	CameraManager* m_cameraManager;
	

	// ���W
	DirectX::SimpleMath::Vector3 m_position;
	// ������]�p
	DirectX::SimpleMath::Quaternion m_initialRotation;
	// ���݂̉�]�p
	DirectX::SimpleMath::Quaternion m_currentRotation;
	// �^�[�Q�b�g���W
	DirectX::SimpleMath::Vector3 m_targetPosition;
	// ���̌���
	DirectX::SimpleMath::Vector3 m_up;

	// ���_���璍���_�܂ł̋���
	DirectX::SimpleMath::Vector3 m_distance;
	// ��������I�u�W�F�N�g�̍��W
	DirectX::SimpleMath::Vector3 m_targetObjectPosition;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// ���x
	float m_sensitivity;
	// ����]�i�x����]�j
	float m_pitch;
	// �c��]�i�w����]�j
	float m_yaw;
};
