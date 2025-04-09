// ============================================
// 
// �t�@�C����: HPGageFrameUI.cpp
// �T�v: HP�̃Q�[�W�t���[��UI
// 
// ����� : �����x��
// 
// ============================================

#include "Framework/pch.h"
#include "Game/UI/HPGageFrameUI.h"
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
HPGageFrameUI::HPGageFrameUI()
	:
	m_isActive{},
	m_objectId{},
	m_transform{},
	m_image{},
	m_material{}
{
	

}

/// <summary>
/// ����������
/// </summary>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="active">�A�N�e�B�u����</param>
void HPGageFrameUI::Initialize(ObjectID objectID, const bool& active)
{
	m_objectId = objectID;
	m_isActive = active;

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
	m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetHPGageFrame(), width, height);
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
/// Transform�̏���������
/// </summary>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
/// <param name="scale">�傫��</param>
void HPGageFrameUI::InitialTransform(
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
void HPGageFrameUI::Update()
{
	//m_material->UpdateConstBuffer();
}

/// <summary>
/// �I������
/// </summary>
void HPGageFrameUI::Finalize()
{

}


/// <summary>
/// �}�e���A���̏�����
/// </summary>
/// <param name="width">�e�N�X�`����</param>
/// <param name="height">�e�N�X�`���c</param>
void HPGageFrameUI::InitialMaterial(int width, int height)
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
void HPGageFrameUI::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	(void)messageID;
}


/// <summary>
/// �����蔻��̃��b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
/// <param name="sender">������������̃I�u�W�F�N�g</param>
void HPGageFrameUI::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}