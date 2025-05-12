#include "pch.h"
#include "Game/Node/Root.h"
#include "Game/Transform/Transform.h"

Root::Root(IObject* parent, IObject::ObjectID objectID,
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Quaternion& rotation,
	const DirectX::SimpleMath::Vector3& scale
)
	:
	NodeBase(),
	m_objectID(objectID),
	m_isActive(true)
{
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


// 初期化する
void Root::Initialize()
{
}

// 更新する
void Root::Update(const float& elapsedTime)
{
	// ノードを更新する
	NodeBase::Update(elapsedTime);
}


// 後処理を行う
void Root::Finalize()
{
}

void Root::OnMessegeAccepted(Message::MessageData messageData)
{
	(void)messageData;
}

// 通知する
void Root::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	(void)type;
	(void)key;
}

void Root::Attach(std::unique_ptr<IObject> node)
{
	// ノードを追加する
	NodeBase::Attach(std::move(node));
	// ノード番号を更新
	NodeBase::GetNodeCountAfterCountUp();
}


void Root::Detach(std::unique_ptr<IObject> node)
{
	// 部品を削除する
	NodeBase::Detach(std::move(node));
}