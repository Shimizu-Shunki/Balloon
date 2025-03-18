#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/Header/MenuScene.h"

#include "Game/UI/MenuButtonUI.h"
#include "Game/UI/TitleLogo.h"
#include "Game/UI/KeyGuideUI.h"
#include "Game/UI/MenuButtonFrameUI.h"


MenuScene::MenuScene()
{
	m_commonResources = CommonResources::GetInstance();
	m_inputManager = CommonResources::GetInstance()->GetInputManager();
}


MenuScene::~MenuScene()
{

}

void MenuScene::Initialize()
{	

	// ���j���[�{�^���@3��
	for (int i = 0; i < 3; i++)
	{
		this->Attach<MenuButtonUI>(IObject::ObjectID::MenuButtonUI, true, 
			{1280.0f / 2.0f , 860.0f + i * 100.0f , 0.0f},
			DirectX::SimpleMath::Quaternion::Identity,
			DirectX::SimpleMath::Vector3::One * 0.8f, 
			static_cast<MenuButtonUI::ButtonType>(i), true);
	}

	// ���j���[�{�^���t���[���@3��
	for (int i = 0; i < 3; i++)
	{
		this->Attach<MenuButtonFrameUI>(IObject::ObjectID::MenuButtonFrameUI, true,
			{ 1280.0f / 2.0f , 865.0f + i * 100.0f , 0.0f },
			DirectX::SimpleMath::Quaternion::Identity,
			DirectX::SimpleMath::Vector3::One * 0.8f,
			static_cast<MenuButtonFrameUI::ButtonType>(i), true);
	}

	// �^�C�g�����S�̒ǉ�
	this->Attach<TitleLogo>(IObject::ObjectID::TitleLogoUI, true,
		{ 1280.0f / 2.0f , 180.0f , 0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One * 0.5f);
	// �L�[�������
	this->Attach<KeyGuideUI>(IObject::ObjectID::KeyGuideUI, true,
		{ 470.0f , 670.0f , 0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One * 0.5f);

	m_buttonIndex = 0;
}

void MenuScene::Start()
{
	// BGM���Đ�����

	// Tween�̐ݒ�
	for (int i = 0; i < 3; i++)
	{
		m_objects[i]->GetTransform()->GetTween()->DOMoveY(360.0f + i * 100.0f, 1.5f).SetDelay(i * 0.5f).SetEase(Tween::EasingType::EaseOutBounce);
		m_objects[i + 3]->GetTransform()->GetTween()->DOMoveY(365.0f + i * 100.0f, 1.5f).SetDelay(i * 0.5f).SetEase(Tween::EasingType::EaseOutBounce);
	}
}

void MenuScene::Update()
{
	this->SelectButton();
}

void MenuScene::Render()
{
	
	//���f���̕`��
	m_commonResources->GetRenderManager()->Render();
}


void MenuScene::Finalize()
{
}

void MenuScene::SelectButton()
{
	if (m_inputManager->OnKeyDown(InputManager::Keys::Up))
	{
		m_buttonIndex--;
		if (m_buttonIndex < 0)
			m_buttonIndex = 2;
	}
	else if (m_inputManager->OnKeyDown(InputManager::Keys::Down))
	{
		m_buttonIndex++;
		if (m_buttonIndex > 2)
			m_buttonIndex = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		MenuButtonUI* button = dynamic_cast<MenuButtonUI*>(m_objects[i].get());
		
		if (i == m_buttonIndex)
			button->SetIsButtonActive(true);
		else
			button->SetIsButtonActive(false);
	}

	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// ���݂̃{�^���̃I�u�W�F�N�g���擾
		MenuButtonFrameUI* buttonFrame = dynamic_cast<MenuButtonFrameUI*>(m_objects[m_buttonIndex + 3].get());

		// �{�^���t���[�����I���ɂ���
		buttonFrame->SetIsButtonActive(true);
	}
	else if (m_inputManager->OnKeyDown(InputManager::Keys::X))
	{
		// ���݂̃{�^���̃I�u�W�F�N�g���擾
		MenuButtonFrameUI* buttonFrame = dynamic_cast<MenuButtonFrameUI*>(m_objects[m_buttonIndex + 3].get());

		// �{�^���t���[�����I���ɂ���
		buttonFrame->SetIsButtonActive(false);
	}
}

