#include "Framework/pch.h"
#include "Game/UI/MenuButtonUI.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"

#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Transform/Transform.h"


const float MenuButtonUI::STAGE_SELECT_WIDTH = 680.0f;
const float MenuButtonUI::SETTING_WIDTH = 680.0f;
const float MenuButtonUI::EXIT_WIDTH = 680.0f;

const float MenuButtonUI::BUTTON_HEIGHT = 123.6f;


MenuButtonUI::MenuButtonUI(MenuButtonUI::ButtonType buttonType, bool buttonActive)
{
	m_buttonType = buttonType;
	m_isButtonActive = buttonActive;

}


void MenuButtonUI::Initialize(ObjectID objectID, const bool& active)
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
	m_image->Initialize(true, m_material.get(), m_transform.get());
	m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetMenuButtonText(), width, height);
	m_image->SetRuleTexture(nullptr);
	m_image->SetIsActive(true);

	// �}�e���A��������������
	this->InitialMaterial(width, height);

	// Transform�̏�����
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
	m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

	// �摜��`��}�l�[�W���[�ɒǉ�����
	commonResources->GetRenderManager()->AddSprite(m_image.get());
}

void MenuButtonUI::InitialTransform(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	m_transform->SetLocalPosition(position);
	m_transform->SetLocalRotation(rotation);
	m_transform->SetLocalScale(scale);
}


void MenuButtonUI::Update()
{
	// m_material->UpdateConstBuffer();
}

void MenuButtonUI::Finalize()
{

}

void MenuButtonUI::SetIsButtonActive(bool buttonActive)
{
	DirectX::SimpleMath::Vector4 rect = m_transform->GetRect();

	if (buttonActive)
		m_transform->SetRect({
			rect.x,
			m_rect.x,
			rect.z,
			m_rect.y
		});
	else
		m_transform->SetRect({
			rect.x,
			m_rect.z,
			rect.z,
			m_rect.w
		});

	m_isButtonActive = buttonActive;
}

void MenuButtonUI::InitialMaterial(int width, int height)
{
	// �}�e���A���̏���������
	auto material = dynamic_cast<DefaultUi*>(m_material.get());
	material->SetPixelShader(CommonResources::GetInstance()->GetResources()->GetShaderResources()->GetUI_PS());
	material->SetWindowSize({ 1280.0f,720.0f });
	material->SetUseTexture(1.0f);
	material->SetUseRuleTexture(0.0f);
	material->SetRuleProgress(0.0f);
	material->SetRuleInverse(0.0f);

	// ���ꂼ��̃{�^���ɍ����e�N�X�`���T�C�Y��ݒ肷��
	switch (m_buttonType)
	{
		case MenuButtonUI::ButtonType::STAGE_SELECT:
			material->SetTextureSize({ STAGE_SELECT_WIDTH , BUTTON_HEIGHT });

			if (m_isButtonActive)
			{
				m_transform->SetRect({ 0.0f , 0.0f , STAGE_SELECT_WIDTH , BUTTON_HEIGHT / 6.0f });
			}
			else
			{
				m_transform->SetRect({ 0.0f , BUTTON_HEIGHT , STAGE_SELECT_WIDTH , BUTTON_HEIGHT * 2.0f });
			}

			m_rect.x = 0.0f;
			m_rect.y = BUTTON_HEIGHT;
			m_rect.z = BUTTON_HEIGHT;
			m_rect.w = BUTTON_HEIGHT * 2.0f;
			break;
		case MenuButtonUI::ButtonType::SETTING:
			material->SetTextureSize({ SETTING_WIDTH , BUTTON_HEIGHT });
			if (m_isButtonActive)
			{
				m_transform->SetRect({ 0.0f , BUTTON_HEIGHT * 2.0f , SETTING_WIDTH , BUTTON_HEIGHT * 3.0f });
			}
			else
			{
				m_transform->SetRect({ 0.0f , BUTTON_HEIGHT * 3.0f , SETTING_WIDTH , BUTTON_HEIGHT * 4.0f });
			}
			m_rect.x = BUTTON_HEIGHT * 2.0f;
			m_rect.y = BUTTON_HEIGHT * 3.0f;
			m_rect.z = BUTTON_HEIGHT * 3.0f;
			m_rect.w = BUTTON_HEIGHT * 4.0f;
			break;
		case MenuButtonUI::ButtonType::EXIT:
			material->SetTextureSize({ EXIT_WIDTH , BUTTON_HEIGHT });
			if (m_isButtonActive)
			{
				m_transform->SetRect({ 0.0f , BUTTON_HEIGHT * 4.0f , EXIT_WIDTH,BUTTON_HEIGHT * 5.0f });
			}
			else
			{
				m_transform->SetRect({ 0.0f , BUTTON_HEIGHT * 5.0f , EXIT_WIDTH,BUTTON_HEIGHT * 6.0f });
			}
			m_rect.x = BUTTON_HEIGHT * 4.0f;
			m_rect.y = BUTTON_HEIGHT * 5.0f;
			m_rect.z = BUTTON_HEIGHT * 5.0f;
			m_rect.w = BUTTON_HEIGHT * 6.0f;
			break;
		default:
			break;

		
	}
	m_rect /= 6.0f;
}