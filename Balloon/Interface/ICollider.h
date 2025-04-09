// ============================================
// 
// �t�@�C����: ICollider.h
// �T�v: �����蔻��i�C���^�[�t�F�[�X�j
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Game/Transform/Transform.h"

class ICollider
{
public:
	enum class ColliderType
	{
		BOX,    // �{�b�N�X
		SPHERE, // �X�t�B�A
	};

public:
	// �f�X�g���N�^
	virtual ~ICollider() = default;

	// ���菈��
	virtual bool DetectCollision(ICollider* collider) = 0;
	// Transform���擾����
	virtual Transform* GetTransform() const = 0;

	// �R���C�_�[�^�C�v���擾����
	virtual ICollider::ColliderType GetColliderType() const = 0;
	// �R���C�_�[�^�C�v��ݒ肷��
	virtual void SetColliderType(ICollider::ColliderType colliderType) = 0;

	// ��Ԃ��擾
	virtual bool GetIsActive() const = 0;
	// ��Ԃ�ݒ肷��
	virtual void SetIsActive(bool active) = 0;

	// �g���K�[���擾����
	virtual bool GetIsTrigger() const = 0;
	// �g���K�[��ݒ肷��
	virtual void SetIsTrigger(bool trigger) = 0;
};