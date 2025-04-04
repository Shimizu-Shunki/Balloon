#pragma once
#include "Interface/IObject.h"
#include "Interface/ICollider.h"

class PhysicsBody;

class AABB
{
private:
	enum CollisionDirection {
		NONE = 0x0,   // 衝突なし
		UP = 0x1,   // 上
		DOWN = 0x2,   // 下
		LEFT = 0x4,   // 左
		RIGHT = 0x8,   // 右
		FRONT = 0x10,  // 前
		BACK = 0x20   // 後
	};

public:

	// コンストラクタ
	AABB();
	// デストラクタ
	~AABB();

public:

	// 判定
	static const bool Intersects(const DirectX::BoundingBox& box1, const DirectX::BoundingBox& box2);
	// 押し戻し
	static const void PushBack(IObject* object1,ICollider* collider1 , PhysicsBody* physicsBody1,
		IObject* object2, ICollider* collider2, PhysicsBody* physicsBody2);
	// 上下左右
	static const int DetermineCollisionDirection(const DirectX::BoundingBox& box1, const DirectX::BoundingBox& box2);
};