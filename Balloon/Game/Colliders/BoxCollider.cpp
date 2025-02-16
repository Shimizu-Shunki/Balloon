#include "Framework/pch.h"
#include "Game/Colliders/BoxCollider.h"
#include "Game/Transform/Transform.h"

BoxCollider::BoxCollider(ICollider::ColliderType type)
{
	// コライダータイプ
	m_colliderType = type;
	// 状態
	m_isActive = true;
	// トリガー
	m_isTrigger = false;

	// Transformを作成
	m_transform = std::make_unique<Transform>();
}

bool BoxCollider::DetectCollision(ICollider* collider)
{

	// ボックス
	DirectX::BoundingBox box;
	// 相手側
	DirectX::BoundingSphere sphere;

	// ボックス1
	DirectX::BoundingBox box1;
	// ボックス2
	DirectX::BoundingBox box2;

	// コライダータイプに応じて衝突判定の処理を変える
	switch (collider->GetColliderType())
	{
		case ICollider::ColliderType::BOX:
			
			box1.Center = m_transform->GetWorldPosition();
			box1.Extents = m_transform->GetWorldScale() / 2.0f;

			box2.Center = collider->GetTransform()->GetWorldPosition();
			box2.Extents = collider->GetTransform()->GetWorldScale() / 2.0f;
			// 判定を行う
			return box1.Intersects(box2);
			break;
		case ICollider::ColliderType::SPHERE:

			box.Center = m_transform->GetWorldPosition();
			box.Extents = m_transform->GetWorldScale() / 2.0f;

			sphere.Center = collider->GetTransform()->GetWorldPosition();
			sphere.Radius = collider->GetTransform()->GetWorldScale().x;
			// 判定を行う
			return box.Intersects(sphere);
			break;

		default:
			return false;
			break;
	}
}
