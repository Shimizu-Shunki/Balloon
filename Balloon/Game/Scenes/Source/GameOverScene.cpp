// ============================================
// 
// �t�@�C����: GameOverScene.cpp
// �T�v: �Q�[���I�[�o�[�V�[��
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/Header/GameOverScene.h"
#include "Interface/IScene.h"
#include "Interface/IObject.h"
#include "Game/Message/SceneMessenger.h"
#include "Game/Cameras/FixedCamera.h"

#include "Game/UI/FailedText.h"
#include "Game/UI/ResultSceneKeyGuide.h"

#include "Framework/StateMachine/StateMachine.h"
#include "Game/States/Fade/FadeInState.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/States/GameOverScene/GameOverMainState.h"


GameOverScene::GameOverScene()
{
	m_commonResources = CommonResources::GetInstance();
}


GameOverScene::~GameOverScene()
{

}

void GameOverScene::Initialize()
{
	

	this->Attach<FailedText>(IObject::ObjectID::FAILED_TEXT_UI, true,
		{ 360.0f , 150.0f , 0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One * 0.5f);

	this->Attach<ResultSceneKeyGuide>(IObject::ObjectID::RESULT_SCENE_KEY_GUIDE_UI, true,
		{ 1280.0f / 3.0f , 720.0f * 0.95f , 0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One * 0.5f);

	// �t�F�[�h�̍쐬
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();

	// �X�e�[�g�̍쐬
	m_fadeInState = std::make_unique<FadeInState>(m_fade.get());
	m_fadeOutState = std::make_unique<FadeOutState>(m_fade.get(), FadeOutState::ChageSceneID::MENU_SCENE);
	m_gameOverMainState = std::make_unique<GameOverMainState>();
	// ���݂̃X�e�[�g��ݒ�
	m_currentState = m_fadeInState.get();

	this->CreateCamera();

	SceneMessenger::GetInstance()->Clear();
	SceneMessenger::GetInstance()->Register(this);
}

void GameOverScene::Start()
{
	// BGM���Đ�����
	m_commonResources->GetAudioManager()->PlayFadeInBgm(XACT_WAVEBANK_SOUNDS_GAMEOVERSCENE, 1.0f);

	m_currentState->PreUpdate();

	m_commonResources->GetRenderManager()->SetDayProgress(0.5f);
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
	// �i�s�x�����Z�b�g
	CommonResources::GetInstance()->GetRenderManager()->SetDayProgress(0.0f);
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
			this->ChangeState(m_gameOverMainState.get());
			break;
		case Message::FADE_OUT:
			this->ChangeState(m_fadeOutState.get());
			break;
		case Message::MAIN:
			this->ChangeState(m_gameOverMainState.get());
			break;
		default:
			break;
	}
}

void GameOverScene::CreateCamera()
{
	// �J�����̍쐬
	std::unique_ptr<ICamera> camera = std::make_unique<FixedCamera>(
		DirectX::SimpleMath::Vector3{ 0.0f , 0.0f , 2.0f },
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up,DirectX::XMConvertToRadians(45.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(-20.0f)) );
	camera->Initialize();

	// �J�������}�l�[�W���[�ɐݒ�
	m_commonResources->GetCameraManager()->Attach(std::move(camera));
}
