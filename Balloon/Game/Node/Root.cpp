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

	// �������W�ݒ�
	m_transform->SetLocalPosition(position);
	// ������]�ݒ�
	m_transform->SetLocalRotation(rotation);
	// �����X�P�[���ݒ�
	m_transform->SetLocalScale(scale);

	// �e������ꍇ�e��ݒ�
	if (parent != nullptr)
		m_transform->SetParent(parent->GetTransform());
}


// ����������
void Root::Initialize()
{
}

// �X�V����
void Root::Update(const float& elapsedTime)
{
	// �m�[�h���X�V����
	NodeBase::Update(elapsedTime);
}


// �㏈�����s��
void Root::Finalize()
{
}

void Root::OnMessegeAccepted(Message::MessageData messageData)
{
	(void)messageData;
}

// �ʒm����
void Root::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
	(void)type;
	(void)key;
}

void Root::Attach(std::unique_ptr<IObject> node)
{
	// �m�[�h��ǉ�����
	NodeBase::Attach(std::move(node));
	// �m�[�h�ԍ����X�V
	NodeBase::GetNodeCountAfterCountUp();
}


void Root::Detach(std::unique_ptr<IObject> node)
{
	// ���i���폜����
	NodeBase::Detach(std::move(node));
}