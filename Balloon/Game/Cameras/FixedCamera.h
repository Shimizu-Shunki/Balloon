#pragma once
#include "Interface/ICamera.h"

class Graphics;

class FixedCamera : public ICamera
{
public:
	// SET
	// �J�������W��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_position = position; }
	// �^�[�Q�b�g���W��ݒ肷��
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& targetPosition) override { m_targetPosition = targetPosition; }
	// ��]�p��ݒ肷��
	void SetRotation(const DirectX::SimpleMath::Quaternion& rotation) override { m_rotation = rotation; }


	// GET
	// �J�������W���擾����
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	// �^�[�Q�b�g���W���擾����
	DirectX::SimpleMath::Vector3 GetTargetPosition() const override { return m_targetPosition; }
	// ��]�p���擾����
	DirectX::SimpleMath::Quaternion GetRotation() const override { return m_rotation; }
	// �r���[�s����擾����
	DirectX::SimpleMath::Matrix GetViewMatrinx() const override { return m_view; }

public:
	// �r���[�s���ݒ肷��
	void CalculateViewMatrix() override;
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
		const DirectX::SimpleMath::Quaternion& rotation) override;
	// �X�V����
	void Update(const float& deltaTime) override;

private:

	// �O���t�B�b�N�X
	Graphics* m_graphics;

	// ���W
	DirectX::SimpleMath::Vector3 m_position;
	// ��]�p
	DirectX::SimpleMath::Quaternion m_rotation;
	// �^�[�Q�b�g���W
	DirectX::SimpleMath::Vector3 m_targetPosition;
	// ���̌���
	DirectX::SimpleMath::Vector3 m_up;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	
};