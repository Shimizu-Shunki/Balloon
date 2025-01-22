#pragma once
#ifndef ICOMPONENT_DEFINED
#define ICOMPONENT_DEFINED
#include "pch.h"
#include "StepTimer.h"
#include "Interface/ICollision.h"
#include <variant>


class IComponent : public ICollision
{
public:
	enum class ObjectID
	{
		NONE,
		OBJECT,
		CLOUD,
		PLAYER,
		ENEMY,
		CHARACTER,
		BALLOON,
	};

public:

	// �I�u�W�F�N�g�A�N�e�B�u���擾����
	virtual bool GetIsActive() const = 0;
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ肷��
	virtual void SetIsActive(bool isActive) = 0;

	// ��{�I�̎擾�ݒ�
	// �Q�b�^�[
	// ���݂̈ʒu���擾����
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	// ���݂̉�]�p���擾����
	virtual DirectX::SimpleMath::Quaternion GetAngle() const = 0;
	// ���݂̑傫�����擾����
	virtual DirectX::SimpleMath::Vector3 GetScale() const = 0;
	// �Z�b�^�[
	// ���W��ݒ肷��
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;
	// ��]��ݒ肷��
	virtual void SetAngle(const DirectX::SimpleMath::Quaternion& angle) = 0;
	// �傫����ݒ肷��
	virtual void SetScale(const DirectX::SimpleMath::Vector3& scale) = 0;


	// �����I�Ȓl���擾�ݒ�
	// �Q�b�^�[
	// �d�͗L������
	virtual bool GetIsGravity() const = 0;
	// �L�l�}�e�B�b�N
	virtual bool GetIsKinematic() const = 0;
	// ����
	virtual float GetMass() const = 0;
	// ���x
	virtual  DirectX::SimpleMath::Vector3 GetVelocity() const = 0;
	// �Z�b�^�[
	// �d�͗L������
	virtual void SetIsGravity(const bool& isGravity) = 0;
	// �L�l�}�e�B�b�N
	virtual void SetIsKinematic(const bool& isKinematic) = 0;
	// ����
	virtual void SetMass(const float& mass) = 0;
	// ���x
	virtual void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) = 0;


	// �I�u�W�F�N�g��ID���擾����
	virtual IComponent::ObjectID GetObjectID() const = 0;
	// ���f�����擾����
	virtual DirectX::Model* GetModel() const = 0;

public:
	// ���z�f�X�g���N�^
	virtual ~IComponent() = default;
	// ����������
	virtual void Initialize(ObjectID objectID , const bool &active) = 0;
	// �X�V����
	virtual void Update(const float elapsedTime,const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) = 0;
	// �`�悷��
	virtual void Render() = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;

	

	

};

#endif		// ICOMPONENT_DEFINED