// ============================================
// 
// �t�@�C����: TPSKeyCamera.h
// �T�v: TPSKeyCamera.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/ICamera.h"

class InputManager;
class Transform;
class PhysicsBody;

class TPSKeyCamera : public ICamera
{
private:
	// ��{�̃s�b�`�p (45�x)
	const float BASE_PITCH =  -DirectX::XM_PIDIV4; //  -45�x
	const float MIN_PITCH  = -DirectX::XM_PIDIV4; // -45�x
	const float MAX_PITCH  =  DirectX::XM_PIDIV4; //  45�x

	// �v���C���[�̑��xY���l�������s�b�`�v�Z
	const float PITCH_OFFSET_FACTOR = 0.5f; // ���x�̉e���x (�����\)

public :
	// Transform���擾����
	Transform* GetTransform() const override { return m_transform.get(); }
	// �r���[�s����擾����
	DirectX::SimpleMath::Matrix GetViewMatrix() const override { return m_view; }


public:
	// �r���[�s���ݒ肷��
	DirectX::SimpleMath::Matrix CalculateViewMatrix() override;
public :
	// �R���X�g���N�^
	TPSKeyCamera(Transform* targetTransform ,PhysicsBody* targetPhysicsBody, DirectX::SimpleMath::Vector3 distance);
	// �f�X�g���N�^
	~TPSKeyCamera() override = default;

	
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;

private:
	// Trasform
	std::unique_ptr<Transform> m_transform;
	// ���̌���
	DirectX::SimpleMath::Vector3 m_up;
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �ǐՂ���Transform
	Transform* m_targetTransform;
	// �ǐՂ��镨������
	PhysicsBody* m_targetPhysicsBody;

	// ������]�p
	DirectX::SimpleMath::Quaternion m_initialRotation;


	// ���_���璍���_�܂ł̋���
	DirectX::SimpleMath::Vector3 m_distance;
	// ���x
	float m_sensitivity;
	// ����]�i�x����]�j
	float m_pitch;
	// �c��]�i�w����]�j
	float m_yaw;
};
