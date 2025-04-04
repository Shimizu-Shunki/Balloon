#include "Framework/pch.h"
#include "Game/UI/MenuButtonFrameUI.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"

#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Transform/Transform.h"


const float MenuButtonFrameUI::STAGE_SELECT_WIDTH = 804.0f;
const float MenuButtonFrameUI::SETTING_WIDTH = 804.0f;
const float MenuButtonFrameUI::EXIT_WIDTH = 804.0f;

const float MenuButtonFrameUI::STAGE_SELECT_WIDTH2 = 814.0f;
const float MenuButtonFrameUI::SETTING_WIDTH2 = 814.0f;
const float MenuButtonFrameUI::EXIT_WIDTH2 = 814.0f;

const float MenuButtonFrameUI::BUTTON_HEIGHT = 123.6f;
const float MenuButtonFrameUI::BUTTON_HEIGHT2 = 116.3f;


MenuButtonFrameUI::MenuButtonFrameUI(MenuButtonFrameUI::ButtonType buttonType, bool buttonActive)
{
	m_buttonType = buttonType;
	m_isButtonActive = buttonActive;
}


void MenuButtonFrameUI::Initialize(ObjectID objectID, const bool& active)
{
	m_objectId = objectID;
	m_isActive = active;

	// 共有リソース
	auto commonResources = CommonResources::GetInstance();
	int width, height;

	// Transformの作成
	m_transform = std::make_unique<Transform>();
	// Imageの作成
	m_image = std::make_unique<Image>();
	m_image2 = std::make_unique<Image>();
	// Materialの作成
	m_material = std::make_unique<DefaultUi>();

	// Imageの初期化
	m_image->Initialize(true, m_material.get(), m_transform.get());
	m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetMenuButtonFrame(), width, height);
	m_image->SetRuleTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetRuleTexture());
	m_image->SetIsActive(true);
	// Image2の初期化
	m_image2->Initialize(true, m_material.get(), m_transform.get());
	m_image2->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetMenuButtonFrame2(), width, height);
	m_image2->SetRuleTexture(nullptr);
	m_image2->SetIsActive(false);

	// マテリアルを初期化する
	this->InitialMaterial(width, height);

	// Transformの初期化
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
	m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

	// 画像を描画マネージャーに追加する
	commonResources->GetRenderManager()->AddSprite(m_image.get());
	commonResources->GetRenderManager()->AddSprite(m_image2.get());
}

void MenuButtonFrameUI::InitialTransform(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	m_transform->SetLocalPosition(position);
	m_transform->SetLocalRotation(rotation);
	m_transform->SetLocalScale(scale);
}


void MenuButtonFrameUI::Update()
{
	// m_material->UpdateConstBuffer();
}

void MenuButtonFrameUI::Finalize()
{

}

void MenuButtonFrameUI::SetIsButtonActive(bool buttonActive)
{
	if (buttonActive)
	{
		m_image->SetIsActive(false);
		m_image2->SetIsActive(true);
	}
	else
	{
		m_image->SetIsActive(true);
		m_image2->SetIsActive(false);
	}

	// マテリアルの初期化処理
	auto material = dynamic_cast<DefaultUi*>(m_material.get());

	// それぞれのボタンに合うテクスチャサイズを設定する
	switch (m_buttonType)
	{
		case MenuButtonFrameUI::ButtonType::STAGE_SELECT:
			if (buttonActive)
			{
				material->SetTextureSize({ STAGE_SELECT_WIDTH2 , BUTTON_HEIGHT2 });
				m_transform->SetRect({ 0.0f , 0.0f , STAGE_SELECT_WIDTH2 , BUTTON_HEIGHT2 / 3.0f });
			}
			else
			{
				material->SetTextureSize({ STAGE_SELECT_WIDTH , BUTTON_HEIGHT });
				m_transform->SetRect({ 0.0f , 0.0f , STAGE_SELECT_WIDTH , BUTTON_HEIGHT / 3.0f });
			}

			break;
		case MenuButtonFrameUI::ButtonType::SETTING:
			if (buttonActive)
			{
				material->SetTextureSize({ SETTING_WIDTH2 , BUTTON_HEIGHT2 });
				m_transform->SetRect({ 0.0f ,BUTTON_HEIGHT2 / 3.0f , SETTING_WIDTH2  , (BUTTON_HEIGHT2 * 2.0f) / 3.0f });
			}
			else
			{
				material->SetTextureSize({ SETTING_WIDTH , BUTTON_HEIGHT });
				m_transform->SetRect({ 0.0f , BUTTON_HEIGHT / 3.0f , SETTING_WIDTH  ,  (BUTTON_HEIGHT * 2.0f) / 3.0f });
			}

			break;
		case MenuButtonFrameUI::ButtonType::EXIT:
			if (buttonActive)
			{
				material->SetTextureSize({ EXIT_WIDTH2 , BUTTON_HEIGHT2 });
				m_transform->SetRect({ 0.0f ,  (BUTTON_HEIGHT2 * 2.0f) / 3.0f , EXIT_WIDTH2  , (BUTTON_HEIGHT2 * 3.0f) / 3.0f });
			}
			else
			{
				material->SetTextureSize({ EXIT_WIDTH , BUTTON_HEIGHT });
				m_transform->SetRect({ 0.0f ,  (BUTTON_HEIGHT * 2.0f) / 3.0f , EXIT_WIDTH  , (BUTTON_HEIGHT * 3.0f) / 3.0f });
			}

			break;
		default:
			break;
	}
	material->UpdateConstBuffer();
	m_isButtonActive = buttonActive;
}

void MenuButtonFrameUI::InitialMaterial(int width, int height)
{
	// マテリアルの初期化処理
	auto material = dynamic_cast<DefaultUi*>(m_material.get());
	material->SetPixelShader(CommonResources::GetInstance()->GetResources()->GetShaderResources()->GetUI_PS());
	material->SetWindowSize({ 1280.0f,720.0f });
	material->SetUseTexture(1.0f);
	material->SetUseRuleTexture(0.0f);
	material->SetRuleProgress(0.0f);
	material->SetRuleInverse(0.0f);

	// それぞれのボタンに合うテクスチャサイズを設定する
	switch (m_buttonType)
	{
		case MenuButtonFrameUI::ButtonType::STAGE_SELECT:
			if (m_isButtonActive)
			{
				material->SetTextureSize({ STAGE_SELECT_WIDTH2 , BUTTON_HEIGHT2 });
				m_transform->SetRect({ 0.0f , 0.0f , STAGE_SELECT_WIDTH2 , BUTTON_HEIGHT2 / 3.0f });
			}
			else
			{
				material->SetTextureSize({ STAGE_SELECT_WIDTH , BUTTON_HEIGHT });
				m_transform->SetRect({ 0.0f , 0.0f , STAGE_SELECT_WIDTH , BUTTON_HEIGHT / 3.0f });
			}

			break;
		case MenuButtonFrameUI::ButtonType::SETTING:
			if (m_isButtonActive)
			{
				material->SetTextureSize({ SETTING_WIDTH2 , BUTTON_HEIGHT2 });
				m_transform->SetRect({ 0.0f ,BUTTON_HEIGHT2 / 3.0f , SETTING_WIDTH2  , (BUTTON_HEIGHT2 * 2.0f) / 3.0f });
			}
			else
			{
				material->SetTextureSize({ SETTING_WIDTH , BUTTON_HEIGHT });
				m_transform->SetRect({ 0.0f , BUTTON_HEIGHT / 3.0f , SETTING_WIDTH  ,  (BUTTON_HEIGHT * 2.0f) / 3.0f });
			}

			break;
		case MenuButtonFrameUI::ButtonType::EXIT:
			if (m_isButtonActive)
			{
				material->SetTextureSize({ EXIT_WIDTH2 , BUTTON_HEIGHT2 });
				m_transform->SetRect({ 0.0f ,  (BUTTON_HEIGHT2 * 2.0f) / 3.0f , EXIT_WIDTH2  , (BUTTON_HEIGHT2 * 3.0f) / 3.0f });
			}
			else
			{
				material->SetTextureSize({ EXIT_WIDTH , BUTTON_HEIGHT });
				m_transform->SetRect({ 0.0f ,  (BUTTON_HEIGHT * 2.0f) / 3.0f , EXIT_WIDTH  , (BUTTON_HEIGHT * 3.0f) / 3.0f });
			}

			break;
		default:
			break;
	}
}

void MenuButtonFrameUI::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	(void)messageID;
}

void MenuButtonFrameUI::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}