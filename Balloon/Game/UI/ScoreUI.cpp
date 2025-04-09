// ============================================
// 
// �t�@�C����: ScoreUI.cpp
// �T�v: �X�R�A��UI
// 
// ����� : �����x��
// 
// ============================================

#include "Framework/pch.h"
#include "Game/UI/ScoreUI.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"

#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Transform/Transform.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ScoreUI::ScoreUI()
	:
	m_isActive{},
	m_objectId{},
	m_transform{},
	m_image{},
	m_material{},
	m_currentScore{}
{
}

/// <summary>
/// ����������
/// </summary>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="active">�A�N�e�B�u����</param>
void ScoreUI::Initialize(ObjectID objectID, const bool& active)
{
	m_objectId = objectID;
	m_isActive = active;

	m_currentScore = 0.0f;

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
	m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetNumbers1(), width, height);
	m_image->SetRuleTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetRuleTexture());
	m_image->SetIsActive(active);

	// �}�e���A��������������
	this->InitialMaterial(width,height);

	DirectX::SimpleMath::Vector4 digits;
	digits.x = static_cast<float>(((int)m_currentScore / 1000) % 10); // 1000�̈�
	digits.y = static_cast<float>(((int)m_currentScore / 100) % 10);  //  100�̈�
	digits.z = static_cast<float>(((int)m_currentScore / 10) % 10);   //   10�̈�
	digits.w = static_cast<float>((int)m_currentScore % 10);          //    1�̈�

	// Transform�̏�����
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
	m_transform->SetRect(digits);
	m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

	commonResources->GetRenderManager()->AddSprite(m_image.get());
}

/// <summary>
/// Transform�̏���������
/// </summary>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�傫��</param>
void ScoreUI::InitialTransform(
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
void ScoreUI::Update()
{
}

/// <summary>
/// �I������
/// </summary>
void ScoreUI::Finalize()
{
}

/// <summary>
/// �}�e���A���̏�����
/// </summary>
/// <param name="width">�e�N�X�`����</param>
/// <param name="height">�e�N�X�`���c</param>
void ScoreUI::InitialMaterial(int width, int height)
{
	auto material = dynamic_cast<DefaultUi*>(m_material.get());

	material->SetPixelShader(CommonResources::GetInstance()->GetResources()->GetShaderResources()->GetScorePS());
	material->SetWindowSize({ 1280.0f,720.0f });
	material->SetTextureSize({ (float)width, (float)height });
	material->SetUseTexture(1.0f);
	material->SetUseRuleTexture(0.0f);
	material->SetRuleProgress(0.0f);
	material->SetRuleInverse(0.0f);
}

/// <summary>
/// �X�R�A��ǉ�
/// </summary>
/// <param name="score">������</param>
void ScoreUI::AddScore(float score)
{
	m_currentScore += score;

	DirectX::SimpleMath::Vector4 digits;
	digits.x = static_cast<float>(((int)m_currentScore / 1000) % 10); // 1000�̈�
	digits.y = static_cast<float>(((int)m_currentScore / 100) % 10);  //  100�̈�
	digits.z = static_cast<float>(((int)m_currentScore / 10) % 10);   //   10�̈�
	digits.w = static_cast<float>((int)m_currentScore % 10);          //    1�̈�

	m_transform->SetRect(digits);
}

/// <summary>
/// �X�R�A�����Z
/// </summary>
/// <param name="score">���Z��</param>
void ScoreUI::SubtractScore(float socre)
{
	m_currentScore += socre;

	DirectX::SimpleMath::Vector4 digits;
	digits.x = static_cast<float>(((int)m_currentScore / 1000) % 10); // 1000�̈�
	digits.y = static_cast<float>(((int)m_currentScore / 100) % 10);  //  100�̈�
	digits.z = static_cast<float>(((int)m_currentScore / 10) % 10);   //   10�̈�
	digits.w = static_cast<float>((int)m_currentScore % 10);          //    1�̈�

	m_transform->SetRect(digits);
}

/// <summary>
/// �X�R�A���[���Ƀ��Z�b�g
/// </summary>
void ScoreUI::ResetScore()
{
	m_currentScore = 0.0f;

	DirectX::SimpleMath::Vector4 digits;
	digits.x = static_cast<float>(((int)m_currentScore / 1000) % 10); // 1000�̈�
	digits.y = static_cast<float>(((int)m_currentScore / 100) % 10);  //  100�̈�
	digits.z = static_cast<float>(((int)m_currentScore / 10) % 10);   //   10�̈�
	digits.w = static_cast<float>((int)m_currentScore % 10);          //    1�̈�

	m_transform->SetRect(digits);
}


/// <summary>
/// ���b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
void ScoreUI::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	switch (messageID)
	{
		case Message::ADD_SCORE_TEN:
			this->AddScore(10.0f);
			break;
		case Message::ADD_SCORE_ONE_HUNDRED:
			this->AddScore(100.0f);
			break;
		case Message::ADD_SCORE_ONE_THOUSAND:
			this->AddScore(1000.0f);
			break;
		case Message::SUBTRACT_SCORE_TEN:
			this->SubtractScore(10.0f);
			break;
		case Message::SUBTRACT_SCORE_ONE_HUNDRED:
			this->SubtractScore(100.0f);
			break;
		case Message::SUBTRACT_SCORE_ONE_THOUSAND:
			this->SubtractScore(1000.0f);
			break;
		case Message::RESET_SCORE:
			this->ResetScore();
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
void ScoreUI::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}