// ============================================
// 
// �t�@�C����: TPSCamera.h
// �T�v: TPSCamera.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/ICamera.h"

class InputManager;
class Transform;

class TPSCamera : public ICamera
{

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
	TPSCamera(Transform* targetTransform , DirectX::SimpleMath::Vector3 distance);
	// �f�X�g���N�^
	~TPSCamera() override = default;

	
	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;

private:
	// �C���v�b�g�}�l�[�W���[
	InputManager* m_inputManager;

	// Trasform
	std::unique_ptr<Transform> m_transform;
	// ���̌���
	DirectX::SimpleMath::Vector3 m_up;
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �ǐՂ���Transform
	Transform* m_targetTransform;
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
