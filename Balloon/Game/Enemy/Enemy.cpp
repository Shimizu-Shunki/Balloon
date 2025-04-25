#include "pch.h"
#include "Game/Enemy/Enemy.h"
#include "Game/Object/Object.h"
#include "Interface/IComposite.h"
#include "Framework/Resources/Resources.h"
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/ResourceKeys.h"
#include "Game/Buffers.h"
#include "Game/Factorys/EnemyFactory.h"



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="angle"></param>
/// <param name="position"></param>
/// <param name="messageID"></param>
Enemy::Enemy(IObject* parent, IObject::ObjectID objectID,
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
Enemy::~Enemy()
{

}


/// <summary>
/// 初期化処理
/// </summary>
void Enemy::Initialize()
{
	// 当たり判定の初期座標を設定
	m_boundingSphere.Center = m_transform->GetLocalPosition();
	// 当たり判定の大きさを設定
	m_boundingSphere.Radius = 2.0f;

	// 体を追加する
	this->Attach(EnemyFactory::CreateEnemyBody(this,
		DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Enemy::Update(const float& elapsedTime)
{
	(void)elapsedTime;

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
void Enemy::Finalize()
{

}

/// <summary>
/// パーツを追加する
/// </summary>
/// <param name="object"></param>
void Enemy::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// パーツを削除する
/// </summary>
/// <param name="turretPart"></param>
void Enemy::Detach(std::unique_ptr<IObject> object)
{

}

/// <summary>
/// メッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
void Enemy::OnMessegeAccepted(Message::MessageID messageID)
{
	(void)messageID;
}

// 通知する
void Enemy::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
}