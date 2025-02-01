#pragma once
#ifndef ICOMPONENT_DEFINED
#define ICOMPONENT_DEFINED
#include "Framework/pch.h"
#include "Framework/StepTimer.h"
#include "Interface/ICollision.h"
#include "Game/Transform/Transform.h"
#include <variant>


class IObject : public ICollision
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

	// Transform�̎擾
	virtual Transform* GetTransform() const = 0;
	
	// �I�u�W�F�N�g��ID���擾����
	virtual IObject::ObjectID GetObjectID() const = 0;
	// ���f�����擾����
	virtual DirectX::Model* GetModel() const = 0;

public:
	// ���z�f�X�g���N�^
	virtual ~IObject() = default;
	// ����������
	virtual void Initialize(ObjectID objectID , const bool &active) = 0;
	// �X�V����
	virtual void Update() = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;
};

#endif		// ICOMPONENT_DEFINED