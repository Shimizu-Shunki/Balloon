// ============================================
// 
// ファイル名: Player.cpp
// 概要: プレイヤーオブジェクト
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Player/Header/Player.h"
#include "Framework/CommonResources.h"
#include "Game/Cameras/TPSKeyCamera.h"
#include "Interface/ICamera.h"
#include "Game/Player/Header/Body.h"
#include "Game/Balloon/Balloon.h"
#include "Interface/ICollider.h"
#include "Game/Colliders/BoxCollider.h"
#include "Game/Colliders/SphereCollider.h"
#include "Game/PhysicsBody/PhysicsBody.h"

#include "Game/States/Player/PlayerIdleState.h"
#include "Game/States/Player/PlayerRunState.h"
#include "Game/States/Player/PlayerAttackState.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="parent">親オブジェクト</param>
Player::Player(IObject* parent)
	:
	m_parent(parent),
	m_childs{},
	m_objectId{},
	m_isActive{},
	m_transform{},
	m_physicsBody{},
	m_boxCollider{},
	m_sphereCollider{},
	m_balloonIndex{}
{
	// インスタンスを取得する
m_commonResources = CommonResources::GetInstance();
// Transformを生成
m_transform = std::make_unique<Transform>();
m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="objectID">オブジェクトID</param>
/// <param name="active">アクティブ設定</param>
void Player::Initialize(ObjectID objectID, const bool& active)
{
	// オブジェクトIDを設定
	m_objectId = objectID;
	// オブジェクトアクティブを設定
	m_isActive = active;

	// 子オブジェクトを生成
	this->CreateChildObjects();
	// 当たり判定を生成
	this->CreateCollider();
	// 物理挙動を生成
	this->CreatePhysicsBody();
	// ステートを作成
	this->CreateStates();

	// TPSカメラを生成
	//std::unique_ptr<ICamera> camera = std::make_unique<TPSKeyCamera>(
	//	m_transform.get(), m_physicsBody.get(), DirectX::SimpleMath::Vector3(0.0f, 0.0f, 10.0f));
	//// カメラを初期化
	//camera->Initialize();
	//// カメラをマネージャーに設定
	//m_commonResources->GetCameraManager()->Attach(std::move(camera));

	// 当たり判定マネージャー登録
	std::vector<ICollider*> colliders;
	colliders.push_back(m_boxCollider.get());
	colliders.push_back(m_sphereCollider.get());
	m_commonResources->GetCollisionManager()->Attach(this, colliders, m_physicsBody.get());

	m_balloonAirAmount = 0.0f;
	m_isFlating = false;
	m_isMoveing = false;
	m_isStage = false;
	m_moveingTime = 0.0f;
}

/// <summary>
/// Transformを初期化
/// </summary>
/// <param name="position">初期座標</param>
/// <param name="rotation">初期回転</param>
/// <param name="scale">初期スケール</param>
void Player::InitialTransform(
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

/// <summary>
/// 更新処理
/// </summary>
void Player::Update()
{
	// キーボードステート
	InputManager* input = m_commonResources->GetInputManager();
	float deltaTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	m_currentState->Update(deltaTime);

	// 上昇の処理を実行
	if (input->OnKey(InputManager::Keys::Space))
	{
   		m_isFlating = true;
	}
	// 上昇の処理を解除
	if (input->OnKeyUp(InputManager::Keys::Space))
	{
		m_isFlating = false;
	}

	// 照準
	if (input->OnKey(InputManager::Keys::X))
	{
		// 照準カメラを起動
	}

	if (input->OnKeyUp(InputManager::Keys::X))
	{
		// 照準解除
	}

	// スキルの発動
	if (input->OnKeyDown(InputManager::Keys::Z) && input->OnKey(InputManager::Keys::X))
	{
		// スキル発動

		// 発動後数秒後に解除
	}

	if (m_isFlating)
	{
		// 風船を大きくする
		m_balloonAirAmount += deltaTime;

		// 風船の大きさを制限
		if (m_balloonAirAmount >= 5.0f)
		{
			m_balloonAirAmount = 5.0f;
		}

		// 風船の大きさに応じて上昇スピードを設定
		float force = m_balloonAirAmount * 0.3f;
		// 重力を設定する
		if(!m_isStage)
		m_physicsBody->SetGravity(force);

		// 力を与える
		// m_physicsBody->SetFoce(m_physicsBody->GetFoce() + force);
	}
	else
	{
		// 風船を小さくする
		m_balloonAirAmount -= deltaTime;

		// 風船の大きさが一番小さくなったら
		if (m_balloonAirAmount <= 0.0f)
		{
			// 力を与えない
			m_balloonAirAmount = -0.3f;

			// 重力を設定する
			//m_physicsBody->SetGravity(m_balloonAirAmount);
		}

		// 風船の大きさに応じて上昇スピードを設定
		float force = m_balloonAirAmount * 0.3f;

		// 重力を設定する
		if (!m_isStage)
		m_physicsBody->SetGravity(force);
	}

	// ステージないにいるかどうかの判定
	m_isStage = this->IsOutsideBounds(m_transform->GetLocalPosition());
	// ステージ外にいるとき
	if (m_isStage)
	{
		// プレイヤーのステージ制限
		DirectX::SimpleMath::Vector3 correction = this->GetCorrectionVector(m_transform->GetLocalPosition());
		// ステージ外にいる場合は押し戻す
		m_physicsBody->AddForce(correction);

		m_physicsBody->SetGravity(m_physicsBody->GetGravity() * 0.2f);
	}

	// 物理挙動の更新処理
	m_physicsBody->Update();

	// 子供オブジェクトを生成
	for (const auto& object : m_childs)
	{
		object->Update();
	}
}

/// <summary>
/// 終了処理
/// </summary>
void Player::Finalize() 
{

}


/// <summary>
/// アタッチ
/// </summary>
/// <param name="object">オブジェクト</param>
/// <param name="objectId">オブジェクトID</param>
/// <param name="position">初期座標</param>
/// <param name="rotation">初期回転</param>
/// <param name="scale">初期スケール</param>
void Player::Attach(std::unique_ptr<IObject> object, IObject::ObjectID objectId,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	// オブジェクトの初期化
	object->Initialize(objectId, true);
	// オブジェクトのTransformを初期化
	object->InitialTransform(position, rotation, scale);

	// 子供に登録
	m_childs.emplace_back(std::move(object));
}

/// <summary>
/// デタッチ
/// </summary>
/// <param name="turretParts">オブジェクト</param>
void Player::Detach(std::unique_ptr<IObject> turretParts)
{

}

/// <summary>
/// ステートを切り替える
/// </summary>
/// <param name="newState">次のステート</param>
void Player::ChangeState(IState* newState)
{
	// 事後処理
	m_currentState->PostUpdate();
	// 現在のステートを切り替える
	m_currentState = newState;
	// 事前処理
	m_currentState->PreUpdate();
}

/// <summary>
/// メッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
void Player::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	switch (messageID)
	{
		case Message::PLAYER_IDLE:
			this->ChangeState(m_idleState.get());
			break;
		case Message::PLAYER_RUN:
			this->ChangeState(m_runState.get());
			break;
		case Message::PLAYER_ATTACK:
			this->ChangeState(m_attackState.get());
			break;
		default:
			break;
	}
}

/// <summary>
/// 当たり判定のメッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
/// <param name="sender">当たった相手のオブジェクト</param>
void Player::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
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
		break;
	case Message::ON_TRIGGER_STAY:
		break;
	case Message::ON_TRIGGER_EXIT:
		break;
	default:
		break;
	}
	(void)sender;
}

DirectX::SimpleMath::Vector3 Player::GetCorrectionVector(const DirectX::SimpleMath::Vector3& position)
{
	DirectX::SimpleMath::Vector3 correction = DirectX::SimpleMath::Vector3::Zero;

	float correctionStrength = 2.0f; // 補正力係数
	DirectX::SimpleMath::Vector3 minBounds = { -5.0f , -5.0f ,-5.0f }; // 最小ステージ範囲
	DirectX::SimpleMath::Vector3 maxBounds = {  5.0f ,  5.0f , 5.0f }; // 最大ステージ範囲

	if (position.x < minBounds.x)
		correction.x = minBounds.x - position.x;
	else if (position.x > maxBounds.x)
		correction.x = maxBounds.x - position.x;

	if (position.y < minBounds.y)
		correction.y = minBounds.y - position.y;
	else if (position.y > maxBounds.y)
		correction.y = maxBounds.y - position.y;

	if (position.z < minBounds.z)
		correction.z = minBounds.z - position.z;
	else if (position.z > maxBounds.z)
		correction.z = maxBounds.z - position.z;

	return correction * correctionStrength;
}

bool Player::IsOutsideBounds(const DirectX::SimpleMath::Vector3& position)
{
	DirectX::SimpleMath::Vector3 minBounds = { -5.0f , -5.0f ,-5.0f }; // 最小ステージ範囲
	DirectX::SimpleMath::Vector3 maxBounds = { 5.0f ,  5.0f , 5.0f }; // 最大ステージ範囲

	return (
		position.x < minBounds.x || position.x > maxBounds.x ||
		position.y < minBounds.y || position.y > maxBounds.y ||
		position.z < minBounds.z || position.z > maxBounds.z
		);
}

/// <summary>
/// 子オブジェクトを生成
/// </summary>
void Player::CreateChildObjects()
{
	// 体オブジェクトを生成
	this->Attach(std::make_unique<Body>(this), ObjectID::PLAYER_BODY);

	// 風船の数を設定
	m_balloonIndex = 3;

	// 風船を生成
	for (int i = 0; i < m_balloonIndex; i++)
	{
		this->Attach(std::make_unique<Balloon>(this), ObjectID::BALLOON,
			DirectX::SimpleMath::Vector3( 0.0f,0.0f,-0.0f ),
			DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
				DirectX::SimpleMath::Vector3::Forward,DirectX::XMConvertToRadians(-20.0f + 20.0f * i)) *
			DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
				DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(-20.0f)
			),
			DirectX::SimpleMath::Vector3::One * 0.03f
			);
	}
}

/// <summary>
/// 当たり判定を作成
/// </summary>
void Player::CreateCollider()
{
	// BoxCollider
	// 体用の当たり判定
	m_boxCollider = std::make_unique<BoxCollider>();                                           // 当たり判定を生成
	m_boxCollider->SetIsActive(true);                                                          // アクティブ設定
	m_boxCollider->SetIsTrigger(false);                                                        // トリガー設定
	m_boxCollider->GetTransform()->SetLocalPosition({ 0.0f,0.75 * 10.0f,0.0f });               // 座標設定
	m_boxCollider->GetTransform()->SetLocalScale({ 1.0f * 10.0f,1.5f * 10.0f ,1.0f * 10.0f }); // スケール設定
	m_boxCollider->GetTransform()->SetParent(m_transform.get());                               // 親のTransformを設定
	// SphereCollider
	// 風船用の当たり判定を設定
	m_sphereCollider = std::make_unique<SphereCollider>();                                     // 当たり判定を生成
	m_sphereCollider->SetIsActive(true);                                                       // アクティブ設定
	m_sphereCollider->SetIsTrigger(true);                                                      // トリガー設定
	m_sphereCollider->GetTransform()->SetLocalPosition({ 0.0f,2.0f * 10.0f,-0.6f * 10.0f });   // 座標を設定
	m_sphereCollider->GetTransform()->SetLocalScale({ 0.4f * 10.0f,0.0f ,0.0f });              // スケール設定
	m_sphereCollider->GetTransform()->SetParent(m_transform.get());                            // 親のTransformを設定
}

/// <summary>
/// 物理挙動を作成
/// </summary>
void Player::CreatePhysicsBody()
{
	// 物理挙動を作成と設定
	m_physicsBody = std::make_unique<PhysicsBody>(this); // 物理挙動を生成
	m_physicsBody->SetIsActive(true);                    // アクティブ設定
	m_physicsBody->SetMass(10.0f);                        // 質量を設定
	m_physicsBody->SetUseGravity(true);                  // 重力設定
	m_physicsBody->SetGravity(-2.0f);
	m_physicsBody->SetIsKinematic(false);                // キネマティック設定
}

/// <summary>
/// ステートを作成
/// </summary>
void Player::CreateStates()
{
	m_idleState = std::make_unique<PlayerIdleState>();
	m_runState = std::make_unique<PlayerRunState>(m_transform.get(),m_physicsBody.get());
	m_attackState = std::make_unique<PlayerAttackState>(this);

	m_currentState = m_idleState.get();
}
											   