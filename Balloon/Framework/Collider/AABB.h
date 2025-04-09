// ============================================
// 
// �t�@�C����: AABB.h
// �T�v: AABB.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IObject.h"
#include "Interface/ICollider.h"

class PhysicsBody;

class AABB
{
private:
	enum CollisionDirection : int
	{
		NONE = 0,   // �Փ˂Ȃ�
		UP,   // ��
		DOWN,   // ��
		LEFT,   // ��
		RIGHT,   // �E
		FRONT,  // �O
		BACK   // ��
	};

public:

	// �R���X�g���N�^
	AABB();
	// �f�X�g���N�^
	~AABB() = default;

public:

	// ����
	static const bool Intersects(const DirectX::BoundingBox& box1, const DirectX::BoundingBox& box2);
	// �����߂�
	static const void PushBack(IObject* object1,ICollider* collider1 , PhysicsBody* physicsBody1,
		IObject* object2, ICollider* collider2, PhysicsBody* physicsBody2);
	// �㉺���E
	static const int DetermineCollisionDirection(const DirectX::BoundingBox& box1, const DirectX::BoundingBox& box2);
};