#pragma once
#include "Interface/ICamera.h"

class Transform;
class CameraManager;

class FollowCamera : public ICamera
{
public:
	// Transform���擾����
	Transform* GetTransform() const { return m_transform.get(); }

public:
	// �r���[�s���ݒ肷��
	DirectX::SimpleMath::Matrix CalculateViewMatrix() override;
public:
	// �R���X�g���N�^
	FollowCamera(Transform* target,DirectX::SimpleMath::Vector3 distance);
	// �f�X�g���N�^
	~FollowCamera() override;

public:

	// ����������
	void Initialize(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& targetPosition,
		const DirectX::SimpleMath::Quaternion& rotation , CameraManager* cameraManager) override;
	// �X�V����
	void Update() override;

private:

	// �J�����}�l�[�W���[
	CameraManager* m_cameraManager;

	// Transform
	std::unique_ptr<Transform> m_transform;
	// �^�[�Q�b�g
	Transform* m_targetTransform;
	// ���̌���
	DirectX::SimpleMath::Vector3 m_up;

	// ���_���璍���_�܂ł̋���
	DirectX::SimpleMath::Vector3 m_distance;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

};