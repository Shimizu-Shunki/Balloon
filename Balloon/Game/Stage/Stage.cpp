// ============================================
// 
// �t�@�C����: Stage.cpp
// �T�v: �X�e�[�W
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Stage/Stage.h"
#include "Framework/CommonResources.h"
#include "Interface/ICollider.h"
#include "Game/Colliders/BoxCollider.h"
#include "Game/PhysicsBody/PhysicsBody.h"
#include "Game/Model3D/Model3D.h"
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/MaterialResources.h"
#include "Game/Player/Header/Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Stage::Stage(IObject* parent)
	:
	m_parent(parent),
	m_transform{}
{
	// Transform�𐶐�
	m_transform = std::make_unique<Transform>();
}

/// <summary>
/// ����������
/// </summary>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="active">���</param>
void Stage::Initialize(ObjectID objectID, const bool& active)
{
	// ���L���\�[�X
	CommonResources* commonResources = CommonResources::GetInstance();

	// �I�u�W�F�N�gID��ݒ�
	m_objectId = objectID;
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ�
	m_isActive = active;
	
	// �����������쐬�Ɛݒ�
	m_physicsBody = std::make_unique<PhysicsBody>(this);
	m_physicsBody->SetIsActive(true);
	m_physicsBody->SetMass(10.0f);
	m_physicsBody->SetUseGravity(false);
	m_physicsBody->SetIsKinematic(true);

	// �����蔻��̍쐬
	this->CreateCollider();
}

/// <summary>
/// Transform��������
/// </summary>
/// <param name="position">�������W</param>
/// <param name="rotation">������]</param>
/// <param name="scale">�����X�P�[��</param>
void Stage::InitialTransform(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	// �ʒu��������
	m_transform->SetLocalPosition(position);
	// ��]�p��������
	m_transform->SetLocalRotation(rotation);
	// �X�P�[����������
	m_transform->SetLocalScale(scale);

	// �g�����X�t�H�[����e�ɐݒ�
	m_transform->SetParent(nullptr);
}

/// <summary>
/// �X�V����
/// </summary>
void Stage::Update() {}

/// <summary>
/// �I������
/// </summary>
void Stage::Finalize() {}			

/// <summary>
/// ���b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
void Stage::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	(void)messageID;
}

/// <summary>
/// ���b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
/// <param name="sender">����</param>
void Stage::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
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

			if (sender->GetObjectID() == ObjectID::PLAYER)
			{
				Player* player = dynamic_cast<Player*>(sender);
				player->GetPhysicsBody()->SetVelocity({
					player->GetPhysicsBody()->GetVelocity().x,
					0.0f,
					player->GetPhysicsBody()->GetVelocity().z
					});

				player->GetPhysicsBody()->AddForce(DirectX::SimpleMath::Vector3::Up);
			}

			break;
		case Message::ON_TRIGGER_STAY:
			break;
		case Message::ON_TRIGGER_EXIT:
			break;
		default:
			break;
	}
}

/// <summary>
/// �����蔻����쐬����
/// </summary>
void Stage::CreateCollider()
{
	std::vector<ICollider*> colliders;

	// �����蔻���ݒ�
	// �X�e�[�W��
	std::unique_ptr<ICollider> box =  std::make_unique<BoxCollider>();
	box->SetIsActive(true);
	box->SetIsTrigger(true);
	box->GetTransform()->SetLocalPosition({0.0f , -6.0f,0.0f });
	box->GetTransform()->SetLocalScale({ 12.0f,1.0f,12.0f });
	box->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(box->GetTransform());

	colliders.push_back(box.get());
	m_boxColliders.push_back(std::move(box));

	// �X�e�[�W��
	box = std::make_unique<BoxCollider>();
	box->SetIsActive(true);
	box->SetIsTrigger(false);
	box->GetTransform()->SetLocalPosition({ 0.0f , 6.0f,0.0f });
	box->GetTransform()->SetLocalScale({ 12.0f,1.0f,12.0f });
	box->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(box->GetTransform());

	colliders.push_back(box.get());
	m_boxColliders.push_back(std::move(box));

	// �X�e�[�W�O
	box = std::make_unique<BoxCollider>();
	box->SetIsActive(true);
	box->SetIsTrigger(false);
	box->GetTransform()->SetLocalPosition({ 0.0f , 0.0f, 6.0f });
	box->GetTransform()->SetLocalScale({ 12.0f,12.0f,1.0f });
	box->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(box->GetTransform());

	colliders.push_back(box.get());
	m_boxColliders.push_back(std::move(box));

	// �X�e�[�W���
	box = std::make_unique<BoxCollider>();
	box->SetIsActive(true);
	box->SetIsTrigger(false);
	box->GetTransform()->SetLocalPosition({ 0.0f , 0.0f, -6.0f });
	box->GetTransform()->SetLocalScale({ 12.0f,12.0f,1.0f });
	box->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(box->GetTransform());

	colliders.push_back(box.get());
	m_boxColliders.push_back(std::move(box));

	// �X�e�[�W�E
	box = std::make_unique<BoxCollider>();
	box->SetIsActive(true);
	box->SetIsTrigger(false);
	box->GetTransform()->SetLocalPosition({ 6.0f , 0.0f, 0.0f });
	box->GetTransform()->SetLocalScale({ 1.0f,12.0f,12.0f });
	box->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(box->GetTransform());

	colliders.push_back(box.get());
	m_boxColliders.push_back(std::move(box));


	// �X�e�[�W��
	box = std::make_unique<BoxCollider>();
	box->SetIsActive(true);
	box->SetIsTrigger(false);
	box->GetTransform()->SetLocalPosition({ -6.0f , 0.0f, 0.0f });
	box->GetTransform()->SetLocalScale({ 1.0f,10.0f,10.0f });
	box->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(box->GetTransform());

	colliders.push_back(box.get());
	m_boxColliders.push_back(std::move(box));

	// �����蔻��}�l�[�W���[�o�^
	CommonResources::GetInstance()->GetCollisionManager()->Attach(this, colliders, m_physicsBody.get());
}