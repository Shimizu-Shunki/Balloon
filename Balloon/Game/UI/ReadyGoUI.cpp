#include "Framework/pch.h"
#include "Game/UI/ReadyGoUI.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"

#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Transform/Transform.h"


ReadyGoUI::ReadyGoUI()
{


}


void ReadyGoUI::Initialize(ObjectID objectID, const bool& active)
{
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
	m_image->Initialize(true, m_material.get(), m_transform.get());
	m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetReadyGoTexture(), width, height);
	m_image->SetRuleTexture(nullptr);
	m_image->SetIsActive(true);

	// ��̃e�L�X�g�̃X�v���C�g�V�[�g�̈׍������Đݒ�
	height /= 2;

	// �}�e���A��������������
	this->InitialMaterial(width, height);

	// Transform�̏�����
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
	m_transform->SetRect({ 0.0f,0.0f,(float)width,(float)height / 2.0f });
	m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

	// �摜��`��}�l�[�W���[�ɒǉ�����
	commonResources->GetRenderManager()->AddSprite(m_image.get());
}

void ReadyGoUI::InitialTransform(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	m_transform->SetLocalPosition(position);
	m_transform->SetLocalRotation(rotation);
	m_transform->SetLocalScale(scale);
}


void ReadyGoUI::Update()
{
	// m_material->UpdateConstBuffer();
}

void ReadyGoUI::Finalize()
{

}

void ReadyGoUI::InitialMaterial(int width, int height)
{
	auto material = dynamic_cast<DefaultUi*>(m_material.get());

	material->SetPixelShader(CommonResources::GetInstance()->GetResources()->GetShaderResources()->GetUI_PS());
	material->SetWindowSize({ 1280.0f,720.0f });
	material->SetTextureSize({ (float)width,(float)height });
	material->SetUseTexture(1.0f);
	material->SetUseRuleTexture(0.0f);
	material->SetRuleProgress(0.0f);
	material->SetRuleInverse(0.0f);
}