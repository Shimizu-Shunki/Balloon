#include "Framework/pch.h"
#include "Game/Cloud/Cloud.h"
#include "Framework/CommonResources.h"

// 当たり判定
#include "Interface/ICollider.h"
#include "Game/Colliders/BoxCollider.h"


Cloud::Cloud(ICamera* camera, IObject* parent)
	:
	m_parent(parent),
	m_camera(camera),
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
	m_transform->SetLocalPosition({ 0.0f,0.0f,0.0f });
	// 回転角を初期化
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	// スケールを初期化
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One * 0.1f);

	// トランスフォームを親に設定
	m_transform->SetParent(nullptr);
	
	// 当たり判定を設定
	m_boxCollider = std::make_unique<BoxCollider>(ICollider::ColliderType::BOX);
	m_boxCollider->SetIsActive(true);
	m_boxCollider->SetIsTrigger(false);
	m_boxCollider->GetTransform()->SetLocalPosition({ 0.0f,1.5f / 2.0f,0.0f });
	m_boxCollider->GetTransform()->SetLocalScale({ 3.0f,1.5f,3.0f });
	m_boxCollider->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(m_boxCollider->GetTransform());

	// 描画管理者に渡す
	m_commonResources->GetRenderManager()->AddModel({ m_transform.get(),m_model });
	// 当たり判定をマネージャーに渡す
	m_commonResources->GetCollisionManager()->Attach(this, m_boxCollider.get());
}

void Cloud::Update()
{
}

void Cloud::Finalize() {}							