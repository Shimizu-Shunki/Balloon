// ============================================
// 
// ファイル名: BoxCollider.h
// 概要: BoxCollider.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/ICollider.h"

class Transform;

class BoxCollider : public ICollider
{
public:
	// 判定処理
	bool DetectCollision(ICollider* collider) override;
	// Transformを取得する
	Transform* GetTransform() const override { return m_transform.get(); }

	// コライダータイプを取得する
	ICollider::ColliderType GetColliderType() const override { return m_colliderType; }
	// コライダータイプを設定する
	void SetColliderType(ICollider::ColliderType colliderType) override { m_colliderType = colliderType; }

	// 状態を取得
	bool GetIsActive() const override { return m_isActive; }
	// 状態を設定する
	void SetIsActive(bool active) override { m_isActive = active; }

	// トリガーを取得する
	bool GetIsTrigger() const override { return m_isTrigger; }
	// トリガーを設定する
	void SetIsTrigger(bool trigger) override { m_isTrigger = trigger; }

public:
	// コンストラクタ
	BoxCollider();
	// デストラクタ
	~BoxCollider() override = default;

private:

	// コライダータイプ
	ICollider::ColliderType m_colliderType;
	// 状態
	bool m_isActive;
	// トリガー
	bool m_isTrigger;

	// Transform
	std::unique_ptr<Transform> m_transform;
};