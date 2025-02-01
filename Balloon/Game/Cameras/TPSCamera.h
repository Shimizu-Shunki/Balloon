#pragma once
#include <Interface/IComponent.h>
#include "Interface/ICamera.h"

class Graphics;
class InputManager;

class TPSCamera : public ICamera
{

public :
	// SET
	// �J�������W��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_position = position; }
	// �^�[�Q�b�g���W��ݒ肷��
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& targetPosition) override { m_targetPosition = targetPosition; }
	// ��]�p��ݒ肷��
	void SetRotation(const DirectX::SimpleMath::Quaternion& rotation) override { m_currentRotation = rotation; }

	void SetTargetObject(IComponent* object) { m_targetObject = object; }


	// GET
	// �J�������W���擾����
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	// �^�[�Q�b�g���W���擾����
	DirectX::SimpleMath::Vector3 GetTargetPosition() const override { return m_targetPosition; }
	// ��]�p���擾����
	DirectX::SimpleMath::Quaternion GetRotation() const override { return m_currentRotation; }
	// �r���[�s����擾����
	DirectX::SimpleMath::Matrix GetViewMatrinx() const override { return m_view; }

public :
	// �R���X�g���N�^
	TPSCamera();
	// �f�X�g���N�^
	~TPSCamera();

	
	// ����������
	void Initialize(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& targetPosition,
		const DirectX::SimpleMath::Quaternion& rotation);
	// �X�V����
	void Update(const float& deltaTime);
	// �r���[�s��v�Z����
	void CalculateViewMatrix();

private:

	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// �C���v�b�g�}�l�[�W���[
	InputManager* m_inputManager;
	// �ǐՂ���I�u�W�F�N�g
	IComponent* m_targetObject;
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
