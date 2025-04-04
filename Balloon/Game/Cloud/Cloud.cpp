#include "Framework/pch.h"
#include "Game/Cloud/Cloud.h"
#include "Framework/CommonResources.h"
#include "Interface/ICollider.h"
#include "Game/Colliders/BoxCollider.h"
#include "Game/PhysicsBody/PhysicsBody.h"
#include "Game/Model3D/Model3D.h"
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/MaterialResources.h"


Cloud::Cloud(IObject* parent)
	:
	m_parent(parent),
	m_transform{}
{
	// Transform�𐶐�
	m_transform = std::make_unique<Transform>();
}

void Cloud::Initialize(ObjectID objectID, const bool& active)
{
	// ���L���\�[�X
	CommonResources* commonResources = CommonResources::GetInstance();

	// �I�u�W�F�N�gID��ݒ�
	m_objectId = objectID;
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ�
	m_isActive = active;
	// 3D���f������������
	m_model = std::make_unique<Model3D>();
	m_model->Initialize(commonResources->GetResources()->GetModelResources()->GetCloudModel(),
		commonResources->GetResources()->GetMaterialResources()->GetCloud(), this
	);
	// �`��}�l�[�W���[�ɓn��
	commonResources->GetRenderManager()->AddModel(m_model.get());

	// �����蔻���ݒ�
	m_boxCollider = std::make_unique<BoxCollider>();
	m_boxCollider->SetIsActive(true);
	m_boxCollider->SetIsTrigger(false);
	m_boxCollider->GetTransform()->SetLocalPosition({ 1.5f,1.5f / 2.0f - 1.0f,0.0f });
	m_boxCollider->GetTransform()->SetLocalScale({ 10.0f,1.5f,10.0f });
	m_boxCollider->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(m_boxCollider->GetTransform());


	// �����������쐬�Ɛݒ�
	m_physicsBody = std::make_unique<PhysicsBody>(this);
	m_physicsBody->SetIsActive(true);
	m_physicsBody->SetMass(10.0f);
	m_physicsBody->SetUseGravity(false);
	m_physicsBody->SetIsKinematic(true);

	// �����蔻��}�l�[�W���[�o�^
	std::vector<ICollider*> colliders;
	colliders.push_back(m_boxCollider.get());
	commonResources->GetCollisionManager()->Attach(this, colliders, m_physicsBody.get());

}

/// <summary>
/// Transform��������
/// </summary>
/// <param name="position">�������W</param>
/// <param name="rotation">������]</param>
/// <param name="scale">�����X�P�[��</param>
void Cloud::InitialTransform(
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
void Cloud::Update() {}

/// <summary>
/// �I������
/// </summary>
void Cloud::Finalize() {}			


void Cloud::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	(void)messageID;
}

void Cloud::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}