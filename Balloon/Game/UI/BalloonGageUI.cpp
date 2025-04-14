// ============================================
// 
// �t�@�C����: BalloonGageUI.cpp
// �T�v: ���D�̃Q�[�WUI
// 
// ����� : �����x��
// 
// ============================================

#include "Framework/pch.h"
#include "Game/UI/BalloonGageUI.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"
#include "Game/Message/ObjectMessenger.h"

#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Transform/Transform.h"

const float BalloonGageUI::SPEED_SLOW = 0.7f;
const float BalloonGageUI::SPEED_NORMAL = 0.5f;
const float BalloonGageUI::SPEED_FAST = 0.3f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BalloonGageUI::BalloonGageUI()
	:
	m_isActive{},
	m_objectId{},
	m_transform{},
	m_image{},
	m_material{},
	m_currentScale{},
	m_isBalloon{},
	m_speed{}
{
}

/// <summary>
/// ����������
/// </summary>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="active">�A�N�e�B�u���</param>
void BalloonGageUI::Initialize(ObjectID objectID, const bool& active)
{
	m_objectId = objectID;
	m_isActive = active;

	m_currentScale = 0.0f;
	m_isBalloon = false;

	m_speed = SPEED_NORMAL;

	// ���L���\�[�X
	auto commonResources = CommonResources::GetInstance();
	int width, height;

	// Transform�̍쐬
	m_transform = std::make_unique<Transform>();
	// Image�̍쐬
	m_image = std::make_unique<Image>();
	// Material�̍쐬
	m_material = std::make_unique<DefaultUi>();

	// Image�̏�����
	m_image->Initialize(active, m_material.get(), m_transform.get());
	m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetBalloonGage(), width, height);
	m_image->SetRuleTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetRuleTexture());
	m_image->SetIsActive(active);

	// �}�e���A��������������
	this->InitialMaterial(width,height);

	// Transform�̏�����
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
	m_transform->SetRect({ 0.0f,0.0f,(float)width,(float)height});
	m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

	commonResources->GetRenderManager()->AddSprite(m_image.get());
}

/// <summary>
/// Transform�̏�����
/// </summary>
/// <param name="position">�ʒu</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
void BalloonGageUI::InitialTransform(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	m_transform->SetLocalPosition(position);
	m_transform->SetLocalRotation(rotation);
	m_transform->SetLocalScale(scale);
}

/// <summary>
/// �X�V����
/// </summary>
void BalloonGageUI::Update()
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

	// �ʒu����
	m_transform->SetLocalPosition({
		m_transform->GetLocalPosition().x,
		600.0f + 33.0f * (std::abs(m_currentScale - 1.0f)),
		0.0f
		});
	// �傫����ݒ�
	float scaled = 0.1f + (m_currentScale * (0.6f - 0.1f));
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One * scaled);

}

/// <summary>
/// �I������
/// </summary>
void BalloonGageUI::Finalize()
{

}

/// <summary>
/// �}�e���A���̏�����
/// </summary>
/// <param name="width">�e�N�X�`����</param>
/// <param name="height">�e�N�X�`���c</param>
void BalloonGageUI::InitialMaterial(int width, int height)
{
	auto material = dynamic_cast<DefaultUi*>(m_material.get());

	material->SetPixelShader(CommonResources::GetInstance()->GetResources()->GetShaderResources()->GetUI_PS());
	material->SetWindowSize({ 1280.0f,720.0f });
	material->SetTextureSize({ (float)width, (float)height });
	material->SetUseTexture(1.0f);
	material->SetUseRuleTexture(0.0f);
	material->SetRuleProgress(0.0f);
	material->SetRuleInverse(0.0f);
}

/// <summary>
/// ���b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
void BalloonGageUI::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	switch (messageID)
	{
		case Message::ON_BALLOON:
			m_isBalloon = true;

			for (int i = 0; i < 3; i++)
				ObjectMessenger::GetInstance()->Dispatch(i + 4, Message::ObjectMessageID::ON_BALLOON);

			break;
		case Message::OFF_BALLOON:
			m_isBalloon = false;

			for (int i = 0; i < 3; i++)
				ObjectMessenger::GetInstance()->Dispatch(i + 4, Message::ObjectMessageID::OFF_BALLOON);
			break;
		case Message::BALLOON_SPEED_SLOW:
			m_speed = SPEED_SLOW;
			break;
		case Message::BALLOON_SPEED_NORMAL:
			m_speed = SPEED_NORMAL;
			break;
		case Message::BALLOON_SPEED_FAST:
			m_speed = SPEED_FAST;
			break;
		default:
			break;
	}
}

/// <summary>
/// �����蔻��̃��b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
/// <param name="sender">������������̃I�u�W�F�N�g</param>
void BalloonGageUI::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}