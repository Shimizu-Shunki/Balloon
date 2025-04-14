// ============================================
// 
// �t�@�C����: LeftArm.cpp
// �T�v: ���r�I�u�W�F�N�g
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Player/Header/LeftArm.h"
#include "Framework/CommonResources.h"
#include "Game/Model3D/Model3D.h"
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/MaterialResources.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
LeftArm::LeftArm(IObject* parent)
	:
	m_parent(parent),
	m_transform{},
	m_objectId{},
	m_isActive{},
	m_model{}
{
	// Transform�𐶐�
	m_transform = std::make_unique<Transform>();
}

/// <summary>
/// ����������
/// </summary>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="active">�A�N�e�B�u�ݒ�</param>
void LeftArm::Initialize(ObjectID objectID, const bool& active)
{
	// ���L���\�[�X
	CommonResources* commonResources = CommonResources::GetInstance();

	// �I�u�W�F�N�gID��ݒ�
	m_objectId = objectID;
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ�
	m_isActive = active;
	
	if (m_objectId == IObject::ObjectID::PLAYER_LEFT_ARM)
	{
		// 3D���f������������
		m_model = std::make_unique<Model3D>();
		m_model->Initialize(commonResources->GetResources()->GetModelResources()->GetPlayerLeftArmModel(),
			commonResources->GetResources()->GetMaterialResources()->GetDefaultPBRLit(), this
		);
	}
	else
	{
		// 3D���f������������
		m_model = std::make_unique<Model3D>();
		m_model->Initialize(commonResources->GetResources()->GetModelResources()->GetPlayerLeftArmModel(),
			commonResources->GetResources()->GetMaterialResources()->GetEnemy(), this
		);
	}
	

	// �`��}�l�[�W���[�ɓn��
	commonResources->GetRenderManager()->AddModel(m_model.get());

}

/// <summary>
/// Transform��������
/// </summary>
/// <param name="position">�������W</param>
/// <param name="rotation">������]</param>
/// <param name="scale">�����X�P�[��</param>
void LeftArm::InitialTransform(
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
	m_transform->SetParent(m_parent->GetTransform());
}

/// <summary>
/// �X�V����
/// </summary>
void LeftArm::Update() {}

/// <summary>
/// �I������
/// </summary>
void LeftArm::Finalize() {}

/// <summary>
/// ���b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
void LeftArm::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	(void)messageID;
}

/// <summary>
/// �����蔻��̃��b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
/// <param name="sender">������������̃I�u�W�F�N�g</param>
void LeftArm::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}