// ============================================
// 
// �t�@�C����: BoxCollider.h
// �T�v: BoxCollider.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/ICollider.h"

class Transform;

class BoxCollider : public ICollider
{
public:
	// ���菈��
	bool DetectCollision(ICollider* collider) override;
	// Transform���擾����
	Transform* GetTransform() const override { return m_transform.get(); }

	// �R���C�_�[�^�C�v���擾����
	ICollider::ColliderType GetColliderType() const override { return m_colliderType; }
	// �R���C�_�[�^�C�v��ݒ肷��
	void SetColliderType(ICollider::ColliderType colliderType) override { m_colliderType = colliderType; }

	// ��Ԃ��擾
	bool GetIsActive() const override { return m_isActive; }
	// ��Ԃ�ݒ肷��
	void SetIsActive(bool active) override { m_isActive = active; }

	// �g���K�[���擾����
	bool GetIsTrigger() const override { return m_isTrigger; }
	// �g���K�[��ݒ肷��
	void SetIsTrigger(bool trigger) override { m_isTrigger = trigger; }

public:
	// �R���X�g���N�^
	BoxCollider();
	// �f�X�g���N�^
	~BoxCollider() override = default;

private:

	// �R���C�_�[�^�C�v
	ICollider::ColliderType m_colliderType;
	// ���
	bool m_isActive;
	// �g���K�[
	bool m_isTrigger;

	// Transform
	std::unique_ptr<Transform> m_transform;
};