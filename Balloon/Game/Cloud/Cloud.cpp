#include "Framework/pch.h"
#include "Game/Cloud/Cloud.h"
#include "Framework/CommonResources.h"

// �����蔻��
#include "Interface/ICollider.h"
#include "Game/Colliders/BoxCollider.h"
// ��������
#include "Game/PhysicsBody/PhysicsBody.h"


Cloud::Cloud(IObject* parent)
	:
	m_parent(parent),
	m_transform{}
{
	// �C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();
}

Cloud::~Cloud()
{

}


void Cloud::Initialize(ObjectID objectID, const bool& active)
{
	// �I�u�W�F�N�gID��ݒ�
	m_objectId = objectID;
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ�
	m_isActive = active;
	// �v���C���[���f���͂Ȃ�
	m_model = m_commonResources->GetResources()->GetCloudModel();

	// Transform���쐬
	m_transform = std::make_unique<Transform>();

	// �ʒu��������
	m_transform->SetLocalPosition({ 0.0f,-1.0f,0.0f });
	// ��]�p��������
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	// �X�P�[����������
	m_transform->SetLocalScale({1.0f,0.3f,1.0f});

	// �g�����X�t�H�[����e�ɐݒ�
	m_transform->SetParent(nullptr);
	
	// �����蔻���ݒ�
	m_boxCollider = std::make_unique<BoxCollider>(ICollider::ColliderType::BOX);
	m_boxCollider->SetIsActive(true);
	m_boxCollider->SetIsTrigger(false);
	m_boxCollider->GetTransform()->SetLocalPosition({ 1.5f,1.5f / 2.0f - 1.0f,0.0f });
	m_boxCollider->GetTransform()->SetLocalScale({ 10.0f,1.5f,10.0f });
	m_boxCollider->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(m_boxCollider->GetTransform());

	// �`��Ǘ��҂ɓn��
	m_commonResources->GetRenderManager()->AddModel({ m_transform.get(),m_model });
	// �����蔻����}�l�[�W���[�ɓn��
	m_commonResources->GetCollisionManager()->Attach(this, m_boxCollider.get());

	// �����������쐬�Ɛݒ�
	m_physicsBody = std::make_unique<PhysicsBody>(this);
	m_commonResources->GetCollisionManager()->PhysicsAttach(this, m_physicsBody.get());
	m_physicsBody->SetIsActive(true);
	m_physicsBody->SetMass(10.0f);
	m_physicsBody->SetUseGravity(false);
	m_physicsBody->SetIsKinematic(true);
}

void Cloud::Update()
{
}

void Cloud::Finalize() {}							