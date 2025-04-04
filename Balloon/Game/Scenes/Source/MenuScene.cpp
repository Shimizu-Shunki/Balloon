#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/Header/MenuScene.h"
#include "Game/Message/SceneMessenger.h"

#include "Game/Fade/Fade.h"

#include "Game/UI/MenuButtonUI.h"
#include "Game/UI/TitleLogo.h"
#include "Game/UI/KeyGuideUI.h"
#include "Game/UI/MenuButtonFrameUI.h"


#include "Game/States/Fade/FadeInState.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/States/MenuScene/MenuMainState.h"
#include "Game/States/MenuScene/MenuSettingState.h"
#include "Game/States/MenuScene/MenuExitState.h"



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

	// �t�F�[�h�̍쐬
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();

	this->CreateStateStateController();

	m_buttonIndex = 0;

	
}

void MenuScene::Start()
{
	// BGM���Đ�����

	SceneMessenger::GetInstance()->Clear();
	SceneMessenger::GetInstance()->Register(this);

	m_currentState->PreUpdate();
}

void MenuScene::Update()
{
	// this->SelectButton();
	float deltaTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();
	
	m_currentState->Update(deltaTime);

	m_fade->Update();
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


void MenuScene::CreateStateStateController()
{
	// �X�e�[�g�̍쐬
	m_fadeInState = std::make_unique<FadeInState>(m_fade.get());
	m_fadeOutState = std::make_unique<FadeOutState>(m_fade.get(), FadeOutState::ChageSceneID::PLAY_SCENE);

	std::vector<IObject*> objects;
	for (int i = 0; i < 6; i++)
	{
		objects.push_back(m_objects[i].get());
	}
	m_menuMainState = std::make_unique<MenuMainState>(objects);

	// ���݂̃X�e�[�g��ݒ�
	m_currentState = m_fadeInState.get();
}


void MenuScene::ChangeState(IState* newState)
{
	// ���㏈��
	m_currentState->PostUpdate();
	// ���݂̃X�e�[�g��؂�ւ���
	m_currentState = newState;
	// ���O����
	m_currentState->PreUpdate();
}

void MenuScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::FADE_IN:
			break;
		case Message::FADE_OUT:
			this->ChangeState(m_fadeOutState.get());
			break;
		case Message::MAIN:
			this->ChangeState(m_menuMainState.get());
		default:
			break;
	}
}
