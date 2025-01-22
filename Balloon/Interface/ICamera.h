#pragma once
#ifndef ICAMERA_DEFINED
#define IICAMERA_DEFINED
#include "pch.h"
#include "StepTimer.h"
#include "Interface/IComponent.h"


class ICamera
{
public:
	// SET
	// �J�������W��ݒ肷��
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;
	// �^�[�Q�b�g���W��ݒ肷��
	virtual void SetTargetPosition(const DirectX::SimpleMath::Vector3& targetPosition) = 0;
	// ��]�p��ݒ肷��
	virtual void SetRotation(const DirectX::SimpleMath::Quaternion& rotation) = 0;
	

	// GET
	// �J�������W���擾����
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	// �^�[�Q�b�g���W���擾����
	virtual DirectX::SimpleMath::Vector3 GetTargetPosition() const = 0;
	// ��]�p���擾����
	virtual DirectX::SimpleMath::Quaternion GetRotation() const = 0;
	// �r���[�s����擾����
	virtual DirectX::SimpleMath::Matrix GetViewMatrinx() const = 0;


public:
	// ���z�f�X�g���N�^
	virtual ~ICamera() = default;
	// ����������
	virtual void Initialize(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& targetPosition,
		const DirectX::SimpleMath::Quaternion& rotation) = 0;
	// �X�V����
	virtual void Update(const float& deltaTime) = 0;
	// �r���[�s��̍쐬
	virtual void CalculateViewMatrix() = 0;
};


#endif		// ICAMERA_DEFINED