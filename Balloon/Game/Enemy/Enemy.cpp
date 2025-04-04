#include "Framework/pch.h"
#include "Game/Enemy/Enemy.h"
#include "Framework/CommonResources.h"

// 子オブジェクト
#include "Game/Player/Header/Body.h"
#include "Game/Balloon/Balloon.h"
// 当たり判定
#include "Interface/ICollider.h"
#include "Game/Colliders/BoxCollider.h"
#include "Game/Colliders/SphereCollider.h"
// 物理挙動
#include "Game/PhysicsBody/PhysicsBody.h"

#include "Game/Player/Header/Player.h"




Enemy::Enemy(IObject* parent)
	:
	m_parent(parent),
	m_transform{}
{
	// インスタンスを取得する
	m_commonResources = CommonResources::GetInstance();
	// Transformを生成
	m_transform = std::make_unique<Transform>();
}

Enemy::~Enemy()
{

}


void Enemy::Initialize(ObjectID objectID, const bool& active)
{
	// オブジェクトIDを設定
	m_objectId = objectID;
	// オブジェクトアクティブを設定
	m_isActive = active;

	// 風船の数を設定
	m_balloonIndex = 3;

	// ボディをアタッチ
	this->Attach(std::make_unique<Body>(this), ObjectID::ENEMY_BODY);

	// 風船を生成
	for (int i = 0; i < 3; i++)
	{
		this->Attach(std::make_unique<Balloon>(this), ObjectID::BALLOON,
			DirectX::SimpleMath::Vector3(0.0f, 3.0f, -0.2f),
			DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
				DirectX::SimpleMath::Vector3::Forward, DirectX::XMConvertToRadians(-20.0f + 20.0f * i)) *
			DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
				DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(-20.0f)
			),
			DirectX::SimpleMath::Vector3::One * 0.03f
		);
	}

	// 当たり判定を設定
	m_boxCollider = std::make_unique<BoxCollider>();
	m_boxCollider->SetIsActive(true);
	m_boxCollider->SetIsTrigger(false);
	m_boxCollider->GetTransform()->SetLocalPosition({ 0.0f,0.75 * 10.0f,0.0f });
	m_boxCollider->GetTransform()->SetLocalScale({ 1.0f * 10.0f,1.5f * 10.0f ,1.0f * 10.0f });
	m_boxCollider->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(m_boxCollider->GetTransform());

	
	m_sphereCollider = std::make_unique<SphereCollider>();
	m_sphereCollider->SetIsActive(true);
	m_sphereCollider->SetIsTrigger(true);
	m_sphereCollider->GetTransform()->SetLocalPosition({ 0.0f,2.0f * 10.0f,-0.6f * 10.0f });
	m_sphereCollider->GetTransform()->SetLocalScale({ 0.4f * 10.0f,1.5f * 10.0f ,1.0f * 10.0f });
	m_sphereCollider->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(m_sphereCollider->GetTransform());

	// 物理挙動を作成と設定
	m_physicsBody = std::make_unique<PhysicsBody>(this);
	m_physicsBody->SetIsActive(true);
	m_physicsBody->SetMass(10.0f);
	m_physicsBody->SetUseGravity(true);
	m_physicsBody->SetIsKinematic(false);

	// 当たり判定をマネージャーに渡す
	std::vector<ICollider*> colliders;
	colliders.push_back(m_boxCollider.get());
	colliders.push_back(m_sphereCollider.get());
	m_commonResources->GetCollisionManager()->Attach(this, colliders , m_physicsBody.get());
}

/// <summary>
/// Transformを初期化
/// </summary>
/// <param name="position">初期座標</param>
/// <param name="rotation">初期回転</param>
/// <param name="scale">初期スケール</param>
void Enemy::InitialTransform(
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
}

void Enemy::Update()
{
	m_physicsBody->Update();

	if (m_balloonIndex == 0)
	{
		m_boxCollider->SetIsActive(false);
	}

	// 子供を更新する
	for (const auto& childObject : m_childs)
	{
		childObject->Update();
	}
}

void Enemy::Finalize() {}


void Enemy::Attach(std::unique_ptr<IObject> object, IObject::ObjectID objectId,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{   
	// パーツの初期化
	object->Initialize(objectId, true);
	// Transformの初期化
	object->InitialTransform(position, rotation, scale);

	// 子供に登録
	m_childs.emplace_back(std::move(object));
}


void Enemy::Detach(std::unique_ptr<IObject> turretParts)
{

}


void Enemy::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	(void)messageID;
}

void Enemy::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
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
				// 上方向に力を加える
				player->GetPhysicsBody()->AddForce(
					DirectX::SimpleMath::Vector3::Up * 2000
				);
				if (m_balloonIndex > 0)
				{
					m_childs[m_balloonIndex]->SetIsActive(false);
					// 風船の数を減らす
					m_balloonIndex--;
				}
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
