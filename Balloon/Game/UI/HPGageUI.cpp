// ============================================
// 
// �t�@�C����: HPGageUI.cpp
// �T�v: HP�̃Q�[�WUI
// 
// ����� : �����x��
// 
// ============================================

#include "Framework/pch.h"
#include "Game/UI/HPGageUI.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"

#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Transform/Transform.h"

const float HPGageUI::SPEED_SLOW   = 0.04f;
const float HPGageUI::SPEED_NORMAL = 0.06f;
const float HPGageUI::SPEED_FAST   = 0.1f;

const float HPGageUI::RECOVERY_DELAY = 2.0f;
const float HPGageUI::HP_OFFSET_FACTOR = 147.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
HPGageUI::HPGageUI()
	:
	m_isActive{},
	m_objectId{},
	m_transform{},
	m_image{},
	m_material{},
	m_speed{},
	m_isHealing{},
	m_currentTime{},
	m_height{},
	m_width{},
	m_baseX{},
	m_hpOffsetFactor{}
{
}

/// <summary>
/// ����������
/// </summary>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="active">�A�N�e�B�u���</param>
void HPGageUI::Initialize(ObjectID objectID, const bool& active)
{
	m_objectId = objectID;
	m_isActive = active;

	// �����X�s�[�h�̓m�[�}��
	m_speed = SPEED_NORMAL;

	m_currentHp = 1.0f;
	m_currentTime = 0.0f;
	m_isHealing = true;

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
	m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetHPGage(), width, height);
	m_image->SetRuleTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetRuleTexture());
	m_image->SetIsActive(active);

	// �}�e���A��������������
	this->InitialMaterial(width,height);

	m_height = (float)height;
	m_width  = (float)width;

	float currentHpWidth = m_currentHp * m_width;

	// Transform�̏�����
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
	m_transform->SetRect({ 0.0f,0.0f,currentHpWidth,(float)height});
	m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

	commonResources->GetRenderManager()->AddSprite(m_image.get());
}

/// <summary>
/// Transform�̏�����
/// </summary>
/// <param name="position">�ʒu</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�X�P�[��</param>
void HPGageUI::InitialTransform(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	m_transform->SetLocalPosition(position);
	m_transform->SetLocalRotation(rotation);
	m_transform->SetLocalScale(scale);

	// �����ʒu��ۑ�
	m_baseX = position.x;
}

/// <summary>
/// �}�e���A���̏�����
/// </summary>
/// <param name="width">�e�N�X�`����</param>
/// <param name="height">�e�N�X�`���c</param>
void HPGageUI::InitialMaterial(int width, int height)
{
	(void)width;

	float original = m_currentHp * 535.0f;

	auto material = dynamic_cast<DefaultUi*>(m_material.get());

	material->SetPixelShader(CommonResources::GetInstance()->GetResources()->GetShaderResources()->GetUI_PS());
	material->SetWindowSize({ 1280.0f,720.0f });
	material->SetTextureSize({ original, (float)height });
	material->SetUseTexture(1.0f);
	material->SetUseRuleTexture(0.0f);
	material->SetRuleProgress(0.0f);
	material->SetRuleInverse(0.0f);
}

/// <summary>
/// �X�V����
/// </summary>
void HPGageUI::Update()
{
	// �o�ߎ��Ԃ̎擾
	float elapsedTime = (float)CommonResources::GetInstance()->GetStepTimer()->GetElapsedSeconds();

	// HP�񕜏���
	this->UpdateHpRecovery(elapsedTime);
	// HP�Q�[�W�̌����ڂ��X�V����
	this->UpdateHpGaugeVisual();
}

/// <summary>
/// �I������
/// </summary>
void HPGageUI::Finalize()
{

}

/// <summary>
/// HP�Q�[�W�̌����ڂ��X�V����
/// </summary>
void HPGageUI::UpdateHpGaugeVisual()
{
	// HP�Q�[�W�̌��ݕ����v�Z
	float currentHpWidth = m_currentHp * m_width;

	// HP�Q�[�W�̈ʒu����
	float xOffset = m_baseX - (HP_OFFSET_FACTOR * std::abs(m_currentHp - 1.0f));

	m_transform->SetLocalPosition({
	   xOffset,
	   m_transform->GetLocalPosition().y,
	   0.0f
	});

	// HP�Q�[�W�̋�`�T�C�Y���X�V
	m_transform->SetRect({ 0.0f, 0.0f, currentHpWidth, m_height });

	// �e�N�X�`���T�C�Y�̍X�V
	auto material = dynamic_cast<DefaultUi*>(m_material.get());
	material->SetTextureSize({ currentHpWidth, m_height });
	material->UpdateConstBuffer();
}

/// <summary>
/// HP�񕜏���
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void HPGageUI::UpdateHpRecovery(float elapsedTime)
{
	// �񕜏���
	if (m_isHealing)
	{
		// �񕜑��x�ɉ�����HP�����Z
		m_currentHp += elapsedTime * m_speed;

		// HP�̏����1.0�ɐ���
		if (m_currentHp >= 1.0f)
			m_currentHp = 1.0f;
	}
	else
	{
		// ��񕜎��̓^�C�}�[��i�߂�
		m_currentTime += elapsedTime;

		// ��莞�Ԍo�ߌ�ɉ񕜂��J�n

		// 2�b��������񕜒��ɂ���
		if (m_currentTime >= RECOVERY_DELAY)
		{
			m_currentTime = 0.0f;
			m_isHealing = true;
		}
	}
}

/// <summary>
/// ���b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
void HPGageUI::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	switch (messageID)
	{
	// HP��0.1���炷
	case Message::SUBTRACT_HP01:
		m_currentHp -= 0.1f;
		break;
	// HP��0.05���炷
	case Message::SUBTRACT_HP005:
		m_currentHp -= 0.05f;
		break;
	// �񕜑��x��x���ݒ�
	case Message::RECOVERY_SPEED_SLOW:
		m_speed = SPEED_SLOW;
		break;
	// �񕜑��x��ʏ�ɐݒ�
	case Message::RECOVERY_SPEED_NORMAL:
		m_speed = SPEED_NORMAL;
		break;
	// �񕜑��x��ʏ�ɐݒ�
	case Message::RECOVERY_SPEED_FAST:
		m_speed = SPEED_FAST;
		break;
	default:
		break;
	}
}

/// <summary>
/// ���b�Z�[�W���󂯎��i�����蔻��j
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
void HPGageUI::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}