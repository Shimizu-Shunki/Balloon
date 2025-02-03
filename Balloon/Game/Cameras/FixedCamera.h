#pragma once
#include "Interface/ICamera.h"

class Graphics;
class Transform;

class FixedCamera : public ICamera
{
public:
	// Transform���擾����
	Transform* GetTransform() const override { return m_transform.get(); }

public:
	// �r���[�s���ݒ肷��
	DirectX::SimpleMath::Matrix CalculateViewMatrix() override;
public:
	// �R���X�g���N�^
	FixedCamera();

	// �f�X�g���N�^
	~FixedCamera() override;

public:

	// ����������
	void Initialize(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& targetPosition,
		const DirectX::SimpleMath::Quaternion& rotation, CameraManager* cameraManager) override;
	// �X�V����
	void Update() override;

private:

	// �J�����}�l�[�W���[
	CameraManager* m_cameraManager;

	// Transform Scale���^�[�Q�b�g�Ƃ��Č���
	std::unique_ptr<Transform> m_transform;
	// ���̌���
	DirectX::SimpleMath::Vector3 m_up;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	
};