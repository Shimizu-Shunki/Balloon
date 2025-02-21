#include "Framework/pch.h"
#include "Game/Cloud/Cloud.h"
#include "Framework/CommonResources.h"
#include "Interface/ICollider.h"
#include "Game/Colliders/BoxCollider.h"
#include "Game/PhysicsBody/PhysicsBody.h"


Cloud::Cloud(IObject* parent)
	:
	m_parent(parent),
	m_transform{}
{
	// Transformを生成
	m_transform = std::make_unique<Transform>();
}

void Cloud::Initialize(ObjectID objectID, const bool& active)
{
	// 共有リソース
	CommonResources* commonResources = CommonResources::GetInstance();

	// オブジェクトIDを設定
	m_objectId = objectID;
	// オブジェクトアクティブを設定
	m_isActive = active;
	// 雲モデルを取得
	m_model = commonResources->GetResources()->GetCloudModel();
	// 描画管理者に渡す
	commonResources->GetRenderManager()->AddModel({ m_transform.get(),m_model });

	// 当たり判定を設定
	m_boxCollider = std::make_unique<BoxCollider>();
	m_boxCollider->SetIsActive(true);
	m_boxCollider->SetIsTrigger(false);
	m_boxCollider->GetTransform()->SetLocalPosition({ 1.5f,1.5f / 2.0f - 1.0f,0.0f });
	m_boxCollider->GetTransform()->SetLocalScale({ 10.0f,1.5f,10.0f });
	m_boxCollider->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(m_boxCollider->GetTransform());
	commonResources->GetCollisionManager()->Attach(this, m_boxCollider.get());

	// 物理挙動を作成と設定
	m_physicsBody = std::make_unique<PhysicsBody>(this);
	m_physicsBody->SetIsActive(true);
	m_physicsBody->SetMass(10.0f);
	m_physicsBody->SetUseGravity(false);
	m_physicsBody->SetIsKinematic(true);
	commonResources->GetCollisionManager()->PhysicsAttach(this, m_physicsBody.get());
}

/// <summary>
/// Transformを初期化
/// </summary>
/// <param name="position">初期座標</param>
/// <param name="rotation">初期回転</param>
/// <param name="scale">初期スケール</param>
void Cloud::InitialTransform(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	// 位置を初期化
	m_transform->SetLocalPosition(position);
	// 回転角を初期化
	m_transform->SetLocalRotation(rotation);
	// スケールを初期化
	m_transform->SetLocalScale(scale);

	// トランスフォームを親に設定
	m_transform->SetParent(nullptr);
}

/// <summary>
/// 更新処理
/// </summary>
void Cloud::Update() {}

/// <summary>
/// 終了処理
/// </summary>
void Cloud::Finalize() {}							