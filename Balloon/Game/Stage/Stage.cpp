// ============================================
// 
// ファイル名: Stage.cpp
// 概要: ステージ
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Stage/Stage.h"
#include "Framework/CommonResources.h"
#include "Interface/ICollider.h"
#include "Game/Colliders/BoxCollider.h"
#include "Game/PhysicsBody/PhysicsBody.h"
#include "Game/Model3D/Model3D.h"
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/MaterialResources.h"
#include "Game/Player/Header/Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
Stage::Stage(IObject* parent)
	:
	m_parent(parent),
	m_transform{}
{
	// Transformを生成
	m_transform = std::make_unique<Transform>();
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="objectID">オブジェクトID</param>
/// <param name="active">状態</param>
void Stage::Initialize(ObjectID objectID, const bool& active)
{
	// 共有リソース
	CommonResources* commonResources = CommonResources::GetInstance();

	// オブジェクトIDを設定
	m_objectId = objectID;
	// オブジェクトアクティブを設定
	m_isActive = active;
	
	// 物理挙動を作成と設定
	m_physicsBody = std::make_unique<PhysicsBody>(this);
	m_physicsBody->SetIsActive(true);
	m_physicsBody->SetMass(10.0f);
	m_physicsBody->SetUseGravity(false);
	m_physicsBody->SetIsKinematic(true);

	// 当たり判定の作成
	this->CreateCollider();
}

/// <summary>
/// Transformを初期化
/// </summary>
/// <param name="position">初期座標</param>
/// <param name="rotation">初期回転</param>
/// <param name="scale">初期スケール</param>
void Stage::InitialTransform(
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
void Stage::Update() {}

/// <summary>
/// 終了処理
/// </summary>
void Stage::Finalize() {}			

/// <summary>
/// メッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
void Stage::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	(void)messageID;
}

/// <summary>
/// メッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
/// <param name="sender">相手</param>
void Stage::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	switch (messageID)
	{
		case Message::ON_COLLISION_ENTER:

			break;
		case Message::ON_COLLISION_STAY:
			break;
		case Message::ON_COLLISION_EXIT:
			break;
		case Message::ON_TRIGGER_ENTER:

			if (sender->GetObjectID() == ObjectID::PLAYER)
			{
				Player* player = dynamic_cast<Player*>(sender);
				player->GetPhysicsBody()->SetVelocity({
					player->GetPhysicsBody()->GetVelocity().x,
					0.0f,
					player->GetPhysicsBody()->GetVelocity().z
					});

				player->GetPhysicsBody()->AddForce(DirectX::SimpleMath::Vector3::Up);
			}

			break;
		case Message::ON_TRIGGER_STAY:
			break;
		case Message::ON_TRIGGER_EXIT:
			break;
		default:
			break;
	}
}

/// <summary>
/// 当たり判定を作成する
/// </summary>
void Stage::CreateCollider()
{
	std::vector<ICollider*> colliders;

	// 当たり判定を設定
	// ステージ下
	std::unique_ptr<ICollider> box =  std::make_unique<BoxCollider>();
	box->SetIsActive(true);
	box->SetIsTrigger(true);
	box->GetTransform()->SetLocalPosition({0.0f , -6.0f,0.0f });
	box->GetTransform()->SetLocalScale({ 12.0f,1.0f,12.0f });
	box->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(box->GetTransform());

	colliders.push_back(box.get());
	m_boxColliders.push_back(std::move(box));

	// ステージ上
	box = std::make_unique<BoxCollider>();
	box->SetIsActive(true);
	box->SetIsTrigger(false);
	box->GetTransform()->SetLocalPosition({ 0.0f , 6.0f,0.0f });
	box->GetTransform()->SetLocalScale({ 12.0f,1.0f,12.0f });
	box->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(box->GetTransform());

	colliders.push_back(box.get());
	m_boxColliders.push_back(std::move(box));

	// ステージ前
	box = std::make_unique<BoxCollider>();
	box->SetIsActive(true);
	box->SetIsTrigger(false);
	box->GetTransform()->SetLocalPosition({ 0.0f , 0.0f, 6.0f });
	box->GetTransform()->SetLocalScale({ 12.0f,12.0f,1.0f });
	box->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(box->GetTransform());

	colliders.push_back(box.get());
	m_boxColliders.push_back(std::move(box));

	// ステージ後ろ
	box = std::make_unique<BoxCollider>();
	box->SetIsActive(true);
	box->SetIsTrigger(false);
	box->GetTransform()->SetLocalPosition({ 0.0f , 0.0f, -6.0f });
	box->GetTransform()->SetLocalScale({ 12.0f,12.0f,1.0f });
	box->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(box->GetTransform());

	colliders.push_back(box.get());
	m_boxColliders.push_back(std::move(box));

	// ステージ右
	box = std::make_unique<BoxCollider>();
	box->SetIsActive(true);
	box->SetIsTrigger(false);
	box->GetTransform()->SetLocalPosition({ 6.0f , 0.0f, 0.0f });
	box->GetTransform()->SetLocalScale({ 1.0f,12.0f,12.0f });
	box->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(box->GetTransform());

	colliders.push_back(box.get());
	m_boxColliders.push_back(std::move(box));


	// ステージ左
	box = std::make_unique<BoxCollider>();
	box->SetIsActive(true);
	box->SetIsTrigger(false);
	box->GetTransform()->SetLocalPosition({ -6.0f , 0.0f, 0.0f });
	box->GetTransform()->SetLocalScale({ 1.0f,10.0f,10.0f });
	box->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(box->GetTransform());

	colliders.push_back(box.get());
	m_boxColliders.push_back(std::move(box));

	// 当たり判定マネージャー登録
	CommonResources::GetInstance()->GetCollisionManager()->Attach(this, colliders, m_physicsBody.get());
}