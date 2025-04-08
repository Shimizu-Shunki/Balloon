#include "Framework/pch.h"
#include "Game/Box/Box.h"
#include "Framework/CommonResources.h"
#include "Game/Model3D/Model3D.h"
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/MaterialResources.h"


Box::Box(IObject* parent)
	:
	m_parent(parent),
	m_transform{}
{
	// Transform�𐶐�
	m_transform = std::make_unique<Transform>();
}

void Box::Initialize(ObjectID objectID, const bool& active)
{
	// ���L���\�[�X
	CommonResources* commonResources = CommonResources::GetInstance();

	// �I�u�W�F�N�gID��ݒ�
	m_objectId = objectID;
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ�
	m_isActive = active;
	// 3D���f������������
	m_model = std::make_unique<Model3D>();
	m_model->Initialize(commonResources->GetResources()->GetModelResources()->GetPlayerHeadModel(),
		commonResources->GetResources()->GetMaterialResources()->GetDefaultPBRLit(), this
	);
	// �`��}�l�[�W���[�ɓn��
	commonResources->GetRenderManager()->AddModel(m_model.get());
}

/// <summary>
/// Transform��������
/// </summary>
/// <param name="position">�������W</param>
/// <param name="rotation">������]</param>
/// <param name="scale">�����X�P�[��</param>
void Box::InitialTransform(
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
void Box::Update() {}

/// <summary>
/// �I������
/// </summary>
void Box::Finalize() {}			


void Box::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	(void)messageID;
}

void Box::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}