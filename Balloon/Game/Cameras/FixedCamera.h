// ============================================
// 
// �t�@�C����: FixedCamera.h
// �T�v: FixedCamera.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/ICamera.h"

class Graphics;
class Transform;

class FixedCamera : public ICamera
{
public:
	// Transform���擾����
	Transform* GetTransform() const override { return m_transform.get(); }
	// �r���[�s����擾����
	DirectX::SimpleMath::Matrix GetViewMatrix() const { return m_view; }

	// �r���[�s���ݒ肷��
	DirectX::SimpleMath::Matrix CalculateViewMatrix() override;
public:
	// �R���X�g���N�^
	FixedCamera(const DirectX::SimpleMath::Vector3& position , const DirectX::SimpleMath::Quaternion& rotation);
	// �f�X�g���N�^
	~FixedCamera() override = default;

	// ����������
	void Initialize() override;
	// �X�V����
	void Update() override;

private:
	// Transform Scale���^�[�Q�b�g�Ƃ��Č���
	std::unique_ptr<Transform> m_transform;
	// ���̌���
	DirectX::SimpleMath::Vector3 m_up;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
};