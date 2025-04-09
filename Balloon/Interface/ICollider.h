// ============================================
// 
// ファイル名: ICollider.h
// 概要: 当たり判定（インターフェース）
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Game/Transform/Transform.h"

class ICollider
{
public:
	enum class ColliderType
	{
		BOX,    // ボックス
		SPHERE, // スフィア
	};

public:
	// デストラクタ
	virtual ~ICollider() = default;

	// 判定処理
	virtual bool DetectCollision(ICollider* collider) = 0;
	// Transformを取得する
	virtual Transform* GetTransform() const = 0;

	// コライダータイプを取得する
	virtual ICollider::ColliderType GetColliderType() const = 0;
	// コライダータイプを設定する
	virtual void SetColliderType(ICollider::ColliderType colliderType) = 0;

	// 状態を取得
	virtual bool GetIsActive() const = 0;
	// 状態を設定する
	virtual void SetIsActive(bool active) = 0;

	// トリガーを取得する
	virtual bool GetIsTrigger() const = 0;
	// トリガーを設定する
	virtual void SetIsTrigger(bool trigger) = 0;
};