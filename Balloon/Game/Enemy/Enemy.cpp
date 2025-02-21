#include "Framework/pch.h"
#include "Game/Enemy/Enemy.h"
#include "Framework/CommonResources.h"

// �q�I�u�W�F�N�g
#include "Game/Player/Header/Body.h"
#include "Game/Balloon/Balloon.h"
// �����蔻��
#include "Interface/ICollider.h"
#include "Game/Colliders/BoxCollider.h"
#include "Game/Colliders/SphereCollider.h"
// ��������
#include "Game/PhysicsBody/PhysicsBody.h"

#include "Game/Jump/Jump.h"
#include "Game/Player/Header/Player.h"




Enemy::Enemy(IObject* parent)
	:
	m_parent(parent),
	m_transform{}
{
	// �C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();
	// Transform�𐶐�
	m_transform = std::make_unique<Transform>();
}

Enemy::~Enemy()
{

}


void Enemy::Initialize(ObjectID objectID, const bool& active)
{
	// �I�u�W�F�N�gID��ݒ�
	m_objectId = objectID;
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ�
	m_isActive = active;
	// �v���C���[���f���͂Ȃ�
	m_model = nullptr;

	// ���D�̐���ݒ�
	m_balloonIndex = 3;

	// �{�f�B���A�^�b�`
	this->Attach(std::make_unique<Body>(this), ObjectID::ENEMY_BODY);

	// ���D�𐶐�
	for (int i = 0; i < 3; i++)
	{
		this->Attach(std::make_unique<Balloon>(this), ObjectID::BALLOON,
			DirectX::SimpleMath::Vector3(0.0f, 3.0f, -0.2f),
			DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
				DirectX::SimpleMath::Vector3::Forward, DirectX::XMConvertToRadians(-20.0f + 20.0f * i)) *
			DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
				DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(-20.0f)
			),
			DirectX::SimpleMath::Vector3::One * 0.03f
		);
	}

	// �����蔻���ݒ�
	m_boxCollider = std::make_unique<BoxCollider>();
	m_boxCollider->SetIsActive(true);
	m_boxCollider->SetIsTrigger(false);
	m_boxCollider->GetTransform()->SetLocalPosition({ 0.0f,0.75 * 10.0f,0.0f });
	m_boxCollider->GetTransform()->SetLocalScale({ 1.0f * 10.0f,1.5f * 10.0f ,1.0f * 10.0f });
	m_boxCollider->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(m_boxCollider->GetTransform());

	// �����蔻����}�l�[�W���[�ɓn��
	m_commonResources->GetCollisionManager()->Attach(this, m_boxCollider.get());

	m_sphereCollider = std::make_unique<SphereCollider>();
	m_sphereCollider->SetIsActive(true);
	m_sphereCollider->SetIsTrigger(true);
	m_sphereCollider->GetTransform()->SetLocalPosition({ 0.0f,2.0f * 10.0f,-0.6f * 10.0f });
	m_sphereCollider->GetTransform()->SetLocalScale({ 0.4f * 10.0f,1.5f * 10.0f ,1.0f * 10.0f });
	m_sphereCollider->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(m_sphereCollider->GetTransform());
	// �����蔻����}�l�[�W���[�ɓn��
	m_commonResources->GetCollisionManager()->Attach(this, m_sphereCollider.get());

	// �����������쐬�Ɛݒ�
	m_physicsBody = std::make_unique<PhysicsBody>(this);
	m_commonResources->GetCollisionManager()->PhysicsAttach(this, m_physicsBody.get());
	m_physicsBody->SetIsActive(true);
	m_physicsBody->SetMass(10.0f);
	m_physicsBody->SetUseGravity(true);
	m_physicsBody->SetIsKinematic(false);
}

/// <summary>
/// Transform��������
/// </summary>
/// <param name="position">�������W</param>
/// <param name="rotation">������]</param>
/// <param name="scale">�����X�P�[��</param>
void Enemy::InitialTransform(
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
}

void Enemy::Update()
{
	m_physicsBody->Update();

	// �q�����X�V����
	for (const auto& childObject : m_childs)
	{
		childObject->Update();
	}
}

void Enemy::Finalize() {}


void Enemy::Attach(std::unique_ptr<IObject> object, IObject::ObjectID objectId,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{   
	// �p�[�c�̏�����
	object->Initialize(objectId, true);
	// Transform�̏�����
	object->InitialTransform(position, rotation, scale);

	// �q���ɓo�^
	m_childs.emplace_back(std::move(object));
}


void Enemy::Detach(std::unique_ptr<IObject> turretParts)
{

}

void Enemy::OnCollisionEnter(IObject* object) { (void)object; }
void Enemy::OnCollisionStay(IObject* object)  { (void)object; }
void Enemy::OnCollisionExit(IObject* object)  { (void)object; }
void Enemy::OnTriggerEnter(IObject* object)   
{ 
	if (object->GetObjectID() == ObjectID::PLAYER)
	{
		Player* player = dynamic_cast<Player*>(object);

		// ������ɗ͂�������
		player->GetPhysicsBody()->SetFoce(
			player->GetPhysicsBody()->GetFoce() + DirectX::SimpleMath::Vector3::Up * 2000
		);
	}
}
void Enemy::OnTriggerStay(IObject* object)    { (void)object; }
void Enemy::OnTriggerExit(IObject* object)    { (void)object; }


