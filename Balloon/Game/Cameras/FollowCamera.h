// ============================================
// 
// �t�@�C����: FollowCamera.h
// �T�v: FollowCamera.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/ICamera.h"

class Transform;


class FollowCamera : public ICamera
{
public:
	// Transform���擾����
	Transform* GetTransform() const { return m_transform.get(); }
	// �r���[�s����擾����
	DirectX::SimpleMath::Matrix GetViewMatrix() const override { return m_view; }

public:
	// �r���[�s���ݒ肷��
	DirectX::SimpleMath::Matrix CalculateViewMatrix() override;
public:
	// �R���X�g���N�^
	FollowCamera(Transform* target,DirectX::SimpleMath::Vector3 distance);
	// �f�X�g���N�^
	~FollowCamera() override = default;

public:

	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;

private:
	// Transform
	std::unique_ptr<Transform> m_transform;
	// ���̌���
	DirectX::SimpleMath::Vector3 m_up;
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �^�[�Q�b�g
	Transform* m_targetTransform;
	// ���_���璍���_�܂ł̋���
	DirectX::SimpleMath::Vector3 m_distance;
};