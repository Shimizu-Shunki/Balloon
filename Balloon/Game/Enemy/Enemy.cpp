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
/// �R���X�g���N�^
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
	// ���N���X
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
	// Transform���쐬
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

/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{

}


/// <summary>
/// ����������
/// </summary>
void Enemy::Initialize()
{
	// �����蔻��̏������W��ݒ�
	m_boundingSphere.Center = m_transform->GetLocalPosition();
	// �����蔻��̑傫����ݒ�
	m_boundingSphere.Radius = 2.0f;

	// �̂�ǉ�����
	this->Attach(EnemyFactory::CreateEnemyBody(this,
		DirectX::SimpleMath::Vector3::Zero,DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One));
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Enemy::Update(const float& elapsedTime)
{
	(void)elapsedTime;

	// Transform�̍X�V����
	m_transform->Update();
	// ���[���h���W�𓖂��蔻��̍��W�ɐݒ�
	m_boundingSphere.Center = m_transform->GetWorldPosition();

	// �q�I�u�W�F�N�g�̍X�V����
	for (const auto& child : m_childs)
	{
		child->Update(elapsedTime);
	}
}

/// <summary>
/// �I������
/// </summary>
void Enemy::Finalize()
{

}

/// <summary>
/// �p�[�c��ǉ�����
/// </summary>
/// <param name="object"></param>
void Enemy::Attach(std::unique_ptr<IObject> object)
{
	m_childs.push_back(std::move(object));
}

/// <summary>
/// �p�[�c���폜����
/// </summary>
/// <param name="turretPart"></param>
void Enemy::Detach(std::unique_ptr<IObject> object)
{

}

/// <summary>
/// ���b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
void Enemy::OnMessegeAccepted(Message::MessageID messageID)
{
	(void)messageID;
}

// �ʒm����
void Enemy::OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key)
{
}