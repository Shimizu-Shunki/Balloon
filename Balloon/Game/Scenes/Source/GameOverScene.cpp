#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/Header/GameOverScene.h"
#include "Interface/IScene.h"
#include "Interface/IObject.h"

#include "Framework/StateMachine/StateMachine.h"
#include "Game/States/Fade/FadeInState.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/States/TitleScene/TitleMainState.h"


GameOverScene::GameOverScene()
{
	m_commonResources = CommonResources::GetInstance();
}


GameOverScene::~GameOverScene()
{

}

void GameOverScene::Initialize()
{
	// �t�F�[�h�̍쐬
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();

	// �X�e�[�g�̍쐬
	m_fadeInState = std::make_unique<FadeInState>(m_fade.get());
	m_fadeOutState = std::make_unique<FadeOutState>(m_fade.get(), FadeOutState::ChageSceneID::TITLE_SCENE);
	m_gameOverMainState = std::make_unique<TitleMainState>();
	// ���݂̃X�e�[�g��ݒ�
	m_currentState = m_fadeInState.get();
}

void GameOverScene::Start()
{
	// BGM���Đ�����
	m_currentState->PreUpdate();
}

void GameOverScene::Update()
{
	const float deltaTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	m_currentState->Update(deltaTime);

	m_fade->Update();
}

void GameOverScene::Render()
{
	//���f���̕`��
	m_commonResources->GetRenderManager()->Render();
}


void GameOverScene::Finalize()
{

}


void GameOverScene::ChangeState(IState* newState)
{
	// ���㏈��
	m_currentState->PostUpdate();
	// ���݂̃X�e�[�g��؂�ւ���
	m_currentState = newState;
	// ���O����
	m_currentState->PreUpdate();
}

void GameOverScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::FADE_IN:
			break;
		case Message::FADE_OUT:
			break;
		default:
			break;
	}
}
