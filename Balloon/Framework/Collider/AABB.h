#pragma once
#include "Interface/IObject.h"
#include "Interface/ICollider.h"

class PhysicsBody;

class AABB
{
private:
	enum CollisionDirection {
		NONE = 0x0,   // �Փ˂Ȃ�
		UP = 0x1,   // ��
		DOWN = 0x2,   // ��
		LEFT = 0x4,   // ��
		RIGHT = 0x8,   // �E
		FRONT = 0x10,  // �O
		BACK = 0x20   // ��
	};

public:

	// �R���X�g���N�^
	AABB();
	// �f�X�g���N�^
	~AABB();

public:

	// ����
	static const bool Intersects(const DirectX::BoundingBox& box1, const DirectX::BoundingBox& box2);
	// �����߂�
	static const void PushBack(IObject* object1,ICollider* collider1 , PhysicsBody* physicsBody1,
		IObject* object2, ICollider* collider2, PhysicsBody* physicsBody2);
	// �㉺���E
	static const int DetermineCollisionDirection(const DirectX::BoundingBox& box1, const DirectX::BoundingBox& box2);
};