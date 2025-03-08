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
#include "Game/Jump/Jump.h"

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
	m_balloonIndex{},
	m_jump{}
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

	
	// ジャンプ処理
	m_jump = std::make_unique<Jump>(m_physicsBody.get());
	m_jump->Initialize();

	// TPSカメラを生成
	//std::unique_ptr<ICamera> camera = std::make_unique<TPSKeyCamera>(
	//	m_transform.get(), m_physicsBody.get(), DirectX::SimpleMath::Vector3(0.0f, 0.0f, 10.0f));
	//// カメラを初期化
	//camera->Initialize();
	// カメラをマネージャーに設定
	//m_commonResources->GetCameraManager()->Attach(std::move(camera));


	// Tween アニメーションを開始
	//m_transform->GetTween()->DOMove(DirectX::SimpleMath::Vector3::One, 2.0f)  // (1,1,1) の座標へ 2.0秒かけて移動
	//	.SetDelay(3.0f)                                                       // 3.0秒の遅延を設定（開始前の待機時間）
	//	.SetEase(Tween::EasingType::EaseOutSine)                              // イージング関数を設定
	//	.SetLoops(3, Tween::LoopType::Yoyo)                                   // 3回繰り返し (Yoyo = 行ったり来たり)
	//	.OnComplete([this] {                                                  // アニメーション完了時のコールバック関数
	//	// ここにアニメーション終了後の処理を書く
	//	});


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
	// 入力に基づく方向ベクトルを取得
	DirectX::SimpleMath::Vector3 movementDirection = this->GetMovementDirection(DirectX::SimpleMath::Quaternion::Identity);

	m_physicsBody->SetFoce(m_physicsBody->GetFoce() + movementDirection * 100.0f);
	
	m_jump->Update();
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

void Player::OnCollisionEnter(IObject* object) { (void)object; }
void Player::OnCollisionStay(IObject* object)  { (void)object; }
void Player::OnCollisionExit(IObject* object)  { (void)object; }
void Player::OnTriggerEnter(IObject* object)   { (void)object; }
void Player::OnTriggerStay(IObject* object)    { (void)object; }
void Player::OnTriggerExit(IObject* object)    { (void)object; }

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
			DirectX::SimpleMath::Vector3( 0.0f,3.0f,-0.2f ),
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

	// 当たり判定をマネージャーに渡す
	m_commonResources->GetCollisionManager()->Attach(this, m_boxCollider.get());
	m_commonResources->GetCollisionManager()->Attach(this, m_sphereCollider.get());
}

/// <summary>
/// 物理挙動を作成
/// </summary>
void Player::CreatePhysicsBody()
{
	// 物理挙動を作成と設定
	m_physicsBody = std::make_unique<PhysicsBody>(this); // 物理挙動を生成
	m_physicsBody->SetIsActive(true);                    // アクティブ設定
	m_physicsBody->SetMass(5.0f);                        // 質量を設定
	m_physicsBody->SetUseGravity(true);                  // 重力設定
	m_physicsBody->SetIsKinematic(false);                // キネマティック設定

	// 当たり判定に物理挙動制御を渡す
	m_commonResources->GetCollisionManager()->PhysicsAttach(this, m_physicsBody.get());
}
											   

// 移動方向を取得する
DirectX::SimpleMath::Vector3 Player::GetMovementDirection(const DirectX::SimpleMath::Quaternion& angle)
{
	// キーボードステート
	InputManager* input = m_commonResources->GetInputManager();

	// 方向
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::Identity;

	// 上キー
	if (input->OnKey(InputManager::Keys::Up))
	{
		direction += DirectX::SimpleMath::Vector3::Backward;
	}
	// 下キー
	if (input->OnKey(InputManager::Keys::Down))
	{
		direction += DirectX::SimpleMath::Vector3::Forward;
	}
	// 右キー
	if (input->OnKey(InputManager::Keys::Right))
	{
		rotation *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-2.0f));
	}
	// 左キー
	if (input->OnKey(InputManager::Keys::Left))
	{
		rotation *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(2.0f));
	}

	m_transform->SetLocalRotation(m_transform->GetLocalRotation() * rotation);

	// プレイヤーの回転角（クォータニオン）に基づいて方向を回転させる
	direction = DirectX::SimpleMath::Vector3::Transform(direction, m_transform->GetLocalRotation());

	// Y成分をゼロにして水平面に制限
	direction.y = 0.0f;

	// 正規化して移動方向を返す
	direction.Normalize();

	return direction;
}