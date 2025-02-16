#include "Framework/pch.h"
#include "Game/Player/Header/Player.h"
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

#include "Game/Jump/Jump.h"




Player::Player(ICamera* camera, IObject* parent)
	:
	m_parent(parent),
	m_camera(camera),
	m_transform{}
{
	// インスタンスを取得する
	m_commonResources = CommonResources::GetInstance();
}

Player::~Player()
{

}


void Player::Initialize(ObjectID objectID, const bool& active)
{
	// オブジェクトIDを設定
	m_objectId = objectID;
	// オブジェクトアクティブを設定
	m_isActive = active;
	// プレイヤーモデルはなし
	m_model = nullptr;

	m_transform = std::make_unique<Transform>();

	// 位置を初期化
	m_transform->SetLocalPosition({ 0.0f,0.0f,0.0f });
	// 回転角を初期化
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	
	// スケールを初期化
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);

	// トランスフォームを親に設定
	/*m_transform->SetParent(nullptr);*/
	// 親のTransformに自分自身を子供に設定
	//m_parent->GetTransform()->SetChild(m_transform.get());
	

	// ボディをアタッチ
	this->Attach(std::make_unique<Body>(this), ObjectID::PLAYER);
	
	// 風船をアタッチ
	for (int i = 0; i < 3; i++)
	{
		std::unique_ptr<IObject> balloon = std::make_unique<Balloon>(this,-20.0f + 20.0f * i);
		balloon->Initialize(ObjectID::BALLOON , true);

		m_childs.emplace_back(std::move(balloon));
	}

	

	// 当たり判定を設定
	m_boxCollider = std::make_unique<BoxCollider>(ICollider::ColliderType::BOX);
	m_boxCollider->SetIsActive(true);
	m_boxCollider->SetIsTrigger(false);
	m_boxCollider->GetTransform()->SetLocalPosition({ 0.0f,0.75 * 10.0f,0.0f });
	m_boxCollider->GetTransform()->SetLocalScale({ 1.0f * 10.0f,1.5f * 10.0f ,1.0f * 10.0f });
	m_boxCollider->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(m_boxCollider->GetTransform());

	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One * 0.1f);
	

	// 当たり判定をマネージャーに渡す
	m_commonResources->GetCollisionManager()->Attach(this, m_boxCollider.get());

	// 物理挙動を作成と設定
	m_physicsBody = std::make_unique<PhysicsBody>(this);
	m_commonResources->GetCollisionManager()->PhysicsAttach(this, m_physicsBody.get());
	m_physicsBody->SetIsActive(true);
	m_physicsBody->SetMass(5.0f);
	m_physicsBody->SetUseGravity(true);
	m_physicsBody->SetIsKinematic(false);

	// ジャンプ処理
	m_jump = std::make_unique<Jump>(m_physicsBody.get());
	m_jump->Initialize();

	
	
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::Up, DirectX::XMConvertToRadians(180.0f)
	));
}

void Player::Update()
{
	// 入力に基づく方向ベクトルを取得
	DirectX::SimpleMath::Vector3 movementDirection = this->GetMovementDirection(DirectX::SimpleMath::Quaternion::Identity);

	m_physicsBody->SetFoce(m_physicsBody->GetFoce() + movementDirection * 100.0f);
	
	
	
	m_jump->Update();
	m_physicsBody->Update();

	// 子供を更新する
	for (const auto& childObject : m_childs)
	{
		childObject->Update();
	}
}

void Player::Finalize() {}


void Player::Attach(std::unique_ptr<IObject> turretParts , IObject::ObjectID objectId)
{
	// パーツの初期化
	turretParts->Initialize(objectId, true);
	// 子供に登録
	m_childs.emplace_back(std::move(turretParts));
}


void Player::Detach(std::unique_ptr<IObject> turretParts)
{

}

void Player::OnCollisionEnter(IObject* object) { (void)object; }
void Player::OnCollisionStay(IObject* object)  { (void)object; }
void Player::OnCollisionExit(IObject* object)  { (void)object; }
void Player::OnTriggerEnter(IObject* object)   { (void)object; }
void Player::OnTriggerStay(IObject* object)    { (void)object; }
void Player::OnTriggerExit(IObject* object)    { (void)object; }
											   

// 移動方向を取得する
DirectX::SimpleMath::Vector3 Player::GetMovementDirection(const DirectX::SimpleMath::Quaternion& angle)
{
	// キーボードステート
	InputManager* input = m_commonResources->GetInputManager();

	// 方向
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	// 上キー
	if (input->OnKey(InputManager::Keys::W))
	{
		direction += DirectX::SimpleMath::Vector3::Forward;
	}
	// 下キー
	if (input->OnKey(InputManager::Keys::S))
	{
		direction += DirectX::SimpleMath::Vector3::Backward;
	}
	// 右キー
	if (input->OnKey(InputManager::Keys::D))
	{
		direction += DirectX::SimpleMath::Vector3::Right;
	}
	// 左キー
	if (input->OnKey(InputManager::Keys::A))
	{
		direction += DirectX::SimpleMath::Vector3::Left;
	}

	// プレイヤーの回転角（クォータニオン）に基づいて方向を回転させる
	direction = DirectX::SimpleMath::Vector3::Transform(direction, angle);

	// Y成分をゼロにして水平面に制限
	direction.y = 0.0f;

	// 正規化して移動方向を返す
	direction.Normalize();

	return direction;
}