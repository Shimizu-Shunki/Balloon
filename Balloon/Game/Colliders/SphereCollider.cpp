// ============================================
// 
// ファイル名: SphereCollider.cpp
// 概要: 球の当たり判定
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Colliders/SphereCollider.h"
#include "Game/Transform/Transform.h"

/// <summary>
/// コンストラクタ
/// </summary>
SphereCollider::SphereCollider()
{
	// コライダータイプ
	m_colliderType = ICollider::ColliderType::SPHERE;
	// 状態
	m_isActive = true;
	// トリガー
	m_isTrigger = false;

	// Transformを作成
	m_transform = std::make_unique<Transform>();
}

/// <summary>
/// 判定を行う
/// </summary>
/// <param name="collider">相手</param>
/// <returns>衝突しているかどうか</returns>
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
			sphere.Radius = m_transform->GetWorldScale().x;

			
			// ワールド行列をセンターとする
			box.Center = collider->GetTransform()->GetWorldPosition();
			// 大きさをTransformのX成分とする
			box.Extents = collider->GetTransform()->GetWorldScale() / 2.0f;

			// 判定を行う
			return sphere.Intersects(box);
			break;
		case ICollider::ColliderType::SPHERE:

			
			// ワールド座標をセンターとする
			sphere.Center = m_transform->GetWorldPosition();
			// 半径をTransformのX成分に設定
			sphere.Radius = m_transform->GetWorldScale().x;

			// ワールド座標をセンターとする
			sphere2.Center = collider->GetTransform()->GetWorldPosition();
			// 半径をTransformのX成分に設定
			sphere2.Radius = collider->GetTransform()->GetWorldScale().x;

			// 判定を行う
			return sphere.Intersects(sphere2);

			break;

		default:
			return false;
			break;
	}
}
