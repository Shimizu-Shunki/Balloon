#include "Framework/pch.h"
#include "Game/Player/Header/Player.h"
#include "Framework/CommonResources.h"

// 子オブジェクト
#include "Game/Player/Header/Body.h"



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
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::Up,DirectX::XMConvertToRadians(180.0f)
	));
	// スケールを初期化
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One * 0.1f);

	// トランスフォームを親に設定
	m_transform->SetParent(nullptr);
	// 親のTransformに自分自身を子供に設定
	//m_parent->GetTransform()->SetChild(m_transform.get());

	// ボディをアタッチ
	this->Attach(std::make_unique<Body>(this), ObjectID::PLAYER);
	// 風船をアタッチ　
	
}

void Player::Update()
{
	// 入力に基づく方向ベクトルを取得
	DirectX::SimpleMath::Vector3 movementDirection = this->GetMovementDirection(DirectX::SimpleMath::Quaternion::Identity);

	movementDirection *= (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	m_transform->SetLocalPosition(m_transform->GetLocalPosition() += movementDirection);

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
	DirectX::Keyboard::State key = m_commonResources->GetInputManager()->GetKeyboardState();

	// 方向
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	// 上キー
	if (key.W)
	{
		direction += DirectX::SimpleMath::Vector3::Forward;
	}
	// 下キー
	if (key.S)
	{
		direction += DirectX::SimpleMath::Vector3::Backward;
	}
	// 右キー
	if (key.D)
	{
		direction += DirectX::SimpleMath::Vector3::Right;
	}
	// 左キー
	if (key.A)
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