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

	// メニューボタン　3つ
	for (int i = 0; i < 3; i++)
	{
		this->Attach<MenuButtonUI>(IObject::ObjectID::MenuButtonUI, true, 
			{1280.0f / 2.0f , 860.0f + i * 100.0f , 0.0f},
			DirectX::SimpleMath::Quaternion::Identity,
			DirectX::SimpleMath::Vector3::One * 0.8f, 
			static_cast<MenuButtonUI::ButtonType>(i), true);
	}

	// メニューボタンフレーム　3つ
	for (int i = 0; i < 3; i++)
	{
		this->Attach<MenuButtonFrameUI>(IObject::ObjectID::MenuButtonFrameUI, true,
			{ 1280.0f / 2.0f , 865.0f + i * 100.0f , 0.0f },
			DirectX::SimpleMath::Quaternion::Identity,
			DirectX::SimpleMath::Vector3::One * 0.8f,
			static_cast<MenuButtonFrameUI::ButtonType>(i), true);
	}



	// タイトルロゴの追加
	this->Attach<TitleLogo>(IObject::ObjectID::TitleLogoUI, true,
		{ 1280.0f / 2.0f , 180.0f , 0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One * 0.5f);
	// キー操作説明
	this->Attach<KeyGuideUI>(IObject::ObjectID::KeyGuideUI, true,
		{ 470.0f , 670.0f , 0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One * 0.5f);

	// フェードの作成
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();

	this->CreateStateStateController();

	m_buttonIndex = 0;

	
}

void MenuScene::Start()
{
	// BGMを再生する

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
	
	//モデルの描画
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
		// 現在のボタンのオブジェクトを取得
		MenuButtonFrameUI* buttonFrame = dynamic_cast<MenuButtonFrameUI*>(m_objects[m_buttonIndex + 3].get());

		// ボタンフレームをオンにする
		buttonFrame->SetIsButtonActive(true);
	}
	else if (m_inputManager->OnKeyDown(InputManager::Keys::X))
	{
		// 現在のボタンのオブジェクトを取得
		MenuButtonFrameUI* buttonFrame = dynamic_cast<MenuButtonFrameUI*>(m_objects[m_buttonIndex + 3].get());

		// ボタンフレームをオンにする
		buttonFrame->SetIsButtonActive(false);
	}
}


void MenuScene::CreateStateStateController()
{
	// ステートの作成
	m_fadeInState = std::make_unique<FadeInState>(m_fade.get());
	m_fadeOutState = std::make_unique<FadeOutState>(m_fade.get(), FadeOutState::ChageSceneID::PLAY_SCENE);

	std::vector<IObject*> objects;
	for (int i = 0; i < 6; i++)
	{
		objects.push_back(m_objects[i].get());
	}
	m_menuMainState = std::make_unique<MenuMainState>(objects);

	// 現在のステートを設定
	m_currentState = m_fadeInState.get();
}


void MenuScene::ChangeState(IState* newState)
{
	// 事後処理
	m_currentState->PostUpdate();
	// 現在のステートを切り替える
	m_currentState = newState;
	// 事前処理
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
