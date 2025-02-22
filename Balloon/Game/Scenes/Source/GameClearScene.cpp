#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/Header/GameClearScene.h"
#include "Interface/IScene.h"
#include "Interface/IObject.h"
#include "Game/UI/ClearText.h"
#include "Framework/StateMachine/StateMachine.h"
#include "Game/States/Fade/FadeInState.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/States/TitleScene/TitleMainState.h"


GameClearScene::GameClearScene()
{
	m_commonResources = CommonResources::GetInstance();
}


GameClearScene::~GameClearScene()
{

}

void GameClearScene::Initialize()
{
	
	m_clearText = std::make_unique<ClearText>();
	m_clearText->Initialize();

	// �t�F�[�h�̍쐬
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();


	// �X�e�[�g�}�V�[���̍쐬
	m_stateMachine = std::make_unique<StateMachine>();

	// �X�e�[�g�R���g���[���[�̍쐬
	auto stateController = std::make_unique<StateController>();

	// �p�����[�^�[�̒ǉ�
	stateController->AddParameters("FadeIN", false);
	stateController->AddParameters("FadeOUT", false);

	// �X�e�[�g�̒ǉ�
	stateController->AddState<FadeInState>("FadeInState", m_fade.get());
	stateController->AddState<TitleMainState>("TitleMainState");
	stateController->AddState<FadeOutState>("FadeOutState", m_fade.get(), FadeOutState::ChageSceneID::TITLE_SCENE);

	// �f�t�H���g�̃X�e�[�g��ݒ�
	stateController->SetDeffultState("FadeInState");

	// �g�����W�V�����̒ǉ�
	stateController->AddTransition("FadeInState", "TitleMainState", "FadeIN", true);
	stateController->AddTransition("TitleMainState", "FadeOutState", "FadeOUT", true);

	// �X�e�[�g�R���g���[���[��ǉ�
	m_stateMachine->AddController(std::move(stateController));


}

void GameClearScene::Start()
{
	// BGM���Đ�����
	m_stateMachine->Start();
}

void GameClearScene::Update()
{
	m_stateMachine->Update();
	m_fade->Update();
	m_clearText->Update();

}

void GameClearScene::Render()
{
	//���f���̕`��
	m_commonResources->GetRenderManager()->Render();
}


void GameClearScene::Finalize()
{

}

