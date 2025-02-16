#include "Framework/pch.h"
#include "Game/Cloud/Cloud.h"
#include "Framework/CommonResources.h"

// 当たり判定
#include "Interface/ICollider.h"
#include "Game/Colliders/BoxCollider.h"
// 物理挙動
#include "Game/PhysicsBody/PhysicsBody.h"


Cloud::Cloud(IObject* parent)
	:
	m_parent(parent),
	m_transform{}
{
	// インスタンスを取得する
	m_commonResources = CommonResources::GetInstance();
}

Cloud::~Cloud()
{

}


void Cloud::Initialize(ObjectID objectID, const bool& active)
{
	// オブジェクトIDを設定
	m_objectId = objectID;
	// オブジェクトアクティブを設定
	m_isActive = active;
	// プレイヤーモデルはなし
	m_model = m_commonResources->GetResources()->GetCloudModel();

	// Transformを作成
	m_transform = std::make_unique<Transform>();

	// 位置を初期化
	m_transform->SetLocalPosition({ 0.0f,-1.0f,0.0f });
	// 回転角を初期化
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	// スケールを初期化
	m_transform->SetLocalScale({1.0f,0.3f,1.0f});

	// トランスフォームを親に設定
	m_transform->SetParent(nullptr);
	
	// 当たり判定を設定
	m_boxCollider = std::make_unique<BoxCollider>(ICollider::ColliderType::BOX);
	m_boxCollider->SetIsActive(true);
	m_boxCollider->SetIsTrigger(false);
	m_boxCollider->GetTransform()->SetLocalPosition({ 1.5f,1.5f / 2.0f - 1.0f,0.0f });
	m_boxCollider->GetTransform()->SetLocalScale({ 10.0f,1.5f,10.0f });
	m_boxCollider->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(m_boxCollider->GetTransform());

	// 描画管理者に渡す
	m_commonResources->GetRenderManager()->AddModel({ m_transform.get(),m_model });
	// 当たり判定をマネージャーに渡す
	m_commonResources->GetCollisionManager()->Attach(this, m_boxCollider.get());

	// 物理挙動を作成と設定
	m_physicsBody = std::make_unique<PhysicsBody>(this);
	m_commonResources->GetCollisionManager()->PhysicsAttach(this, m_physicsBody.get());
	m_physicsBody->SetIsActive(true);
	m_physicsBody->SetMass(10.0f);
	m_physicsBody->SetUseGravity(false);
	m_physicsBody->SetIsKinematic(true);
}

void Cloud::Update()
{
}

void Cloud::Finalize() {}							