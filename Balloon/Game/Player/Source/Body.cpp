#include "pch.h"
#include "Game/Player/Header/Body.h"
#include "Game/Player/Character.h"
#include "Framework/CollisionManager.h"
#include "Game/Balloon/Balloon.h"
#include "Framework/InputManager.h"
#include "Game/Player/Enemy.h"
#include "Game/Collider/Collider.h"
#include "Game/Player/Hand.h"
#include "Game/Player/Jump.h"
#include "Framework/Resources.h"

#include "Game/Player/Header/LeftArm.h"
#include "Game/Player/Header/LeftFoot.h"
#include "Game/Player/Header/RightArm.h"
#include "Game/Player/Header/RightFoot.h"


Body::Body(CollisionManager* collisionManger,IComponent* parent, const int balloonIndex, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle))
{
	m_collisionManager = collisionManger;
	m_inputManager = InputManager::GetInstance();
}

Body::~Body()
{

}


void Body::Initialize(ObjectID objectID, const bool& active)
{
	// オブジェクトIDを設定
	m_objectId = objectID;
	// オブジェクトアクティブを設定
	m_isActive = active;

	m_isKinematic = false;

	// オブジェクトIDを設定
	m_objectId = ObjectID::PLAYER;

	// 現在の座標を初期化
	m_currentPosition = m_initialPosition;
	// 現在の回転を初期化
	m_rotationTurretAngle = m_initialAngle;
	// 大きさを初期化
	m_scale = DirectX::SimpleMath::Vector3::One;

	// モデルを取得する
	m_model = Resources::GetInstance()->GetPlayerBodyModel();

	// アタッチする
	// 左腕
	//this->Attach(std::make_unique<LeftArm>());
	//// 左足
	//this->Attach(std::make_unique<LeftFoot>());
	//// 右腕
	//this->Attach(std::make_unique<RightArm>());
	//// 右足
	//this->Attach(std::make_unique<RightFoot>());
}

void Body::Update(const float elapsedTime, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{

	// 当たり判定の更新
	for (auto& collider : m_colliders)
	{
		collider->Update(m_currentPosition);
	}
	// 子オブジェクトを更新する
	for (auto& child : m_child)
	{
		// 風船を更新する
		child->Update(elapsedTime, m_currentPosition, m_currentAngle);
	}
}

// 描画処理
void Body::Render()
{
	// 当たり判定の更新
	for (auto& collider : m_colliders)
	{
		collider->DebugRender();
	}
	// 子オブジェクトを描画する
	for (auto& childes : m_child)
	{
		// 子オブジェクトを描画する
		childes->Render();
	}
}

void Body::Attach(std::unique_ptr<IComponent> turretParts)
{
	// 砲塔部品を追加する
	turretParts->Initialize(IComponent::ObjectID::PLAYER, true);
	// 子オブジェクトをアタッチ
	m_child.emplace_back(std::move(turretParts));
}

void Body::OnCollisionEnter(IComponent* component)
{
	m_gravity = 0.0f;
	m_velocity.y = 0.0f;
	m_isGravity = false;
}

void Body::OnCollisionStay(IComponent* component)
{

}

void Body::OnCollisionExit(IComponent* component)
{
	m_isGravity = true;
}



void Body::OnTriggerEnter(IComponent* component)
{
}
void Body::OnTriggerStay(IComponent* component)
{
}
void Body::OnTriggerExit(IComponent* component)
{
}



void Body::Detach(std::unique_ptr<IComponent> turretParts)
{

}

void Body::Finalize()
{

}


