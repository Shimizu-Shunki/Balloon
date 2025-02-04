#include "Framework/pch.h"
#include "Game/Colliders/SphereCollider.h"
#include "Game/Transform/Transform.h"

SphereCollider::SphereCollider(ICollider::ColliderType type)
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

bool SphereCollider::DetectCollision(ICollider* collider)
{

	// スフィア
	DirectX::BoundingSphere sphere;
	// 相手側
	DirectX::BoundingBox box;

	// スフィア
	DirectX::BoundingSphere sphere1;
	// スフィア
	DirectX::BoundingSphere sphere2;

	// コライダータイプに応じて衝突判定の処理を変える
	switch (collider->GetColliderType())
	{
		case ICollider::ColliderType::BOX :
			// ワールド座標をセンターとする
			sphere.Center = m_transform->GetWorldPosition();
			// 半径をTransformのX成分に設定
			sphere.Radius = m_transform->GetLocalScale().x;

			
			// ワールド行列をセンターとする
			box.Center = collider->GetTransform()->GetWorldPosition();
			// 大きさをTransformのX成分とする
			box.Extents = collider->GetTransform()->GetLocalScale() / 2.0f;

			// 判定を行う
			return sphere.Intersects(box);
			break;
		case ICollider::ColliderType::SPHERE:

			
			// ワールド座標をセンターとする
			sphere.Center = m_transform->GetWorldPosition();
			// 半径をTransformのX成分に設定
			sphere.Radius = m_transform->GetLocalScale().x;

			// ワールド座標をセンターとする
			sphere2.Center = collider->GetTransform()->GetWorldPosition();
			// 半径をTransformのX成分に設定
			sphere2.Radius = collider->GetTransform()->GetLocalScale().x;

			// 判定を行う
			return sphere.Intersects(sphere2);

			break;

		default:
			return false;
			break;
	}
}
