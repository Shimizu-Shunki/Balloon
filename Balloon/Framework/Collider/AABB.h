// ============================================
// 
// ファイル名: AABB.h
// 概要: AABB.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
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
		NONE = 0,   // 衝突なし
		UP,   // 上
		DOWN,   // 下
		LEFT,   // 左
		RIGHT,   // 右
		FRONT,  // 前
		BACK   // 後
	};

public:

	// コンストラクタ
	AABB();
	// デストラクタ
	~AABB() = default;

public:

	// 判定
	static const bool Intersects(const DirectX::BoundingBox& box1, const DirectX::BoundingBox& box2);
	// 押し戻し
	static const void PushBack(IObject* object1,ICollider* collider1 , PhysicsBody* physicsBody1,
		IObject* object2, ICollider* collider2, PhysicsBody* physicsBody2);
	// 上下左右
	static const int DetermineCollisionDirection(const DirectX::BoundingBox& box1, const DirectX::BoundingBox& box2);
};