#include "pch.h"
#include "Game/Player/Player.h"
#include "Game/Object/Object.h"
#include "Interface/IComposite.h"
#include "Game/RenderableObjects/PlayerRenderableObject.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Game/Buffers.h"
#include "Game/Factorys/PlayerFactory.h"

// ステート
#include "Game/States/Player/PlayerIdleState.h"
#include "Game/States/Player/PlayerRunState.h"
#include "Game/States/Player/PlayerAttackState.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="angle"></param>
/// <param name="position"></param>
/// <param name="messageID"></param>
Player::Player(IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale,
	Message::MessageID messageID)
	:
	// 基底クラス
	Object(
		0.0f,
		0.0f,
		0.0f,
		0.0f
	),
	m_isActive(true),
	m_objectNumber(Object::CountUpNumber()),
	m_objectID(objectID),
	m_messageID(messageID),
	m_parent(parent),
	m_transform{},
	m_childs {}
{
	// Transformを作成
	m_transform = std::make_unique<Transform>();
	
	// 初期座標設定
	m_transform->SetLocalPosition(position);
	// 初期回転設定
	m_transform->SetLocalRotation(rotation);
	// 初期スケール設定
	m_transform->SetLocalScale(scale);

	// 親がいる場合親を設定
	if (parent != nullptr)
		m_transform->SetParent(parent->GetTransform());
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{

}


/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize()
{
	// 当たり判定の初期座標を設定
	m_boundingSphere.Center = m_transform->GetLocalPosition();
	// 当たり判定の大きさを設定
	m_boundingSphere.Radius = 2.0f;

	// ステートの作成
	m_playerIdleState = std::make_unique<PlayerIdleState>();
	m_playerRunState = std::make_unique<PlayerRunState>(this);
	m_playerAttackState = std::make_unique<PlayerAttackState>();
	// ステートの初期化処理
	m_playerIdleState->Initialize();
	m_playerRunState->Initialize();
	m_playerAttackState->Initialize();
	// 現在のステートを設定
	Object::SetState(m_playerIdleState.get());

	// 体を追加する
	this->Attach(PlayerFactory::CreatePlayerBody(this,
		DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));


	// オブジェクトのカウントをリセット
	Object::ResetNumber();
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Player::Update(const float& elapsedTime)
{
	(void)elapsedTime;

	Object::Update(elapsedTime);

	// 操舵力(加速度 = 操舵力 / 質量)から加速度を計算する
	DirectX::SimpleMath::Vector3 acceleration = DirectX::SimpleMath::Vector3::Zero;
	// 速度に加速度を加算する
	m_velocity += acceleration * elapsedTime;
	// 現在の位置を更新する
	m_transform->SetLocalPosition(m_transform->GetLocalPosition() + m_velocity * elapsedTime);

	// Transformの更新処理
	m_transform->Update();
	// ワールド座標を当たり判定の座標に設定
	m_boundingSphere.Center = m_transform->GetWorldPosition();

	// 子オブジェクトの更新処理
	for (const auto& child : m_childs)
	{
		child->Update(elapsedTime);
	}
}

/// <summary>
/// 終了処理
/// </summary>
void Player::Finalize()
{

}

/// <summary>
/// パーツを追加する
/// </summary>
/// <param name="object"></param>
void Player::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// パーツを削除する
/// </summary>
/// <param name="turretPart"></param>
void Player::Detach(std::unique_ptr<IObject> object)
{

}

/// <summary>
/// メッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
void Player::OnMessegeAccepted(Message::MessageID messageID)
{
	(void)messageID;
}


// 通知する
void Player::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	switch (key)
	{
		case DirectX::Keyboard::Keys::Up:

			if (type == KeyType::ON_KEY_DOWN)
			{
				if(Object::GetState() != m_playerRunState.get())
				Object::ChangeState(m_playerRunState.get());
				m_playerRunState->SetIsForward(true);
			}
			if (type == KeyType::ON_KEY_UP)
			{
				if (Object::GetState() == m_playerRunState.get())
					Object::ChangeState(m_playerIdleState.get());
			}
				

			break;
		case DirectX::Keyboard::Keys::Down:

			if (type == KeyType::ON_KEY_DOWN)
			{
				if (Object::GetState() != m_playerRunState.get())
					Object::ChangeState(m_playerRunState.get());
				m_playerRunState->SetIsBackward(true);
			}
			if (type == KeyType::ON_KEY_UP)
			{
				if (Object::GetState() == m_playerRunState.get())
					Object::ChangeState(m_playerIdleState.get());
			}

			break;
		case DirectX::Keyboard::Keys::Left:

			// プレイヤーに回転角を与える
			m_transform->SetLocalRotation(
				DirectX::SimpleMath::Quaternion::Concatenate(
					m_transform->GetLocalRotation(),
					DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
						DirectX::SimpleMath::Vector3::Up,
						DirectX::XMConvertToRadians(2.0f))
				)
			);
			break;
		case DirectX::Keyboard::Keys::Right:

			// プレイヤーに回転角を与える
			m_transform->SetLocalRotation(
				DirectX::SimpleMath::Quaternion::Concatenate(
					m_transform->GetLocalRotation(),
					DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
						DirectX::SimpleMath::Vector3::Up,
						DirectX::XMConvertToRadians(-2.0f))
				)
			);
			break;

		default:
			break;
	}



}