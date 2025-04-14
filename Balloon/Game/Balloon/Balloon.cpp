#include "Framework/pch.h"
#include "Game/Balloon/Balloon.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/ModelResources.h"
#include "Game/Model3D/Model3D.h"
#include "Framework/Resources/MaterialResources.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
Balloon::Balloon(IObject* parent)
	:
	m_parent(parent),
	m_transform{},
	m_objectId{},
	m_isActive{},
	m_model{},
	m_currentScale{},
	m_initScale{},
	m_initPosition{},
	m_speed(0.5f),
	m_isBalloon(false)
{
	// Transform�𐶐�
	m_transform = std::make_unique<Transform>();
}

/// <summary>
/// ����������
/// </summary>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="active">�A�N�e�B�u�ݒ�</param>
void Balloon::Initialize(ObjectID objectID, const bool& active)
{
	// ���L���\�[�X
	CommonResources* commonResources = CommonResources::GetInstance();

	// �I�u�W�F�N�gID��ݒ�
	m_objectId = objectID;
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ�
	m_isActive = active;
	// 3D���f������������
	m_model = std::make_unique<Model3D>();
	m_model->Initialize(commonResources->GetResources()->GetModelResources()->GetBalloonModel(),
		commonResources->GetResources()->GetMaterialResources()->GetBalloon(), this
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
void Balloon::InitialTransform(
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

	m_initScale = scale;
	m_initPosition = position;

	// �g�����X�t�H�[����e�ɐݒ�
	m_transform->SetParent(m_parent->GetTransform());
}

/// <summary>
/// �X�V����
/// </summary>
void Balloon::Update()
{
	float elapsedTime = (float)CommonResources::GetInstance()->GetStepTimer()->GetElapsedSeconds();

	// �I���̏ꍇ
	if (m_isBalloon)
	{
		m_currentScale += elapsedTime * m_speed;

		if (m_currentScale >= 1.0f)
		{
			m_currentScale = 1.0f;
		}
	}
	else
	{
		m_currentScale -= elapsedTime * m_speed;

		if (m_currentScale <= 0.0f)
		{
			m_currentScale = 0.0f;
		}
	}

	// ���W��ݒ�
	m_transform->SetLocalPosition({ m_initPosition.x ,m_initPosition.y - (m_currentScale * 20.0f) , m_initPosition.z });
	// �X�P�[����ݒ�
	m_transform->SetLocalScale(m_initScale * (m_currentScale + 1.0f));
}

/// <summary>
/// �I������
/// </summary>
void Balloon::Finalize() {}


void Balloon::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	switch (messageID)
	{
		case Message::ON_BALLOON:
			m_isBalloon = true;
			break;
		case Message::OFF_BALLOON:
			m_isBalloon = false;
	}
}

void Balloon::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}