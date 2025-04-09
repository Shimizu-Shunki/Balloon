// ============================================
// 
// �t�@�C����: GameClearScene.cpp
// �T�v: �Q�[���N���A�V�[��
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/Header/GameClearScene.h"
#include "Interface/IScene.h"
#include "Interface/IObject.h"
#include "Framework/StateMachine/StateMachine.h"
#include "Game/States/Fade/FadeInState.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/States/GameClearScene/GameClearMainState.h"
#include "Game/Cameras/FixedCamera.h"

#include "Game/UI/ClearText.h"
#include "Game/UI/ResultSceneKeyGuide.h"
#include "Game/Message/SceneMessenger.h"

GameClearScene::GameClearScene()
{
	m_commonResources = CommonResources::GetInstance();
}


GameClearScene::~GameClearScene()
{

}

void GameClearScene::Initialize()
{
	// �t�F�[�h�̍쐬
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();

	this->Attach<ClearText>(IObject::ObjectID::CLEAR_TEXT_UI, true,
		{ 360.0f , 150.0f , 0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One * 0.5f);

	this->Attach<ResultSceneKeyGuide>(IObject::ObjectID::RESULT_SCENE_KEY_GUIDE_UI, true,
		{ 1280.0f / 3.0f , 720.0f * 0.95f , 0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One * 0.5f);

	// �X�e�[�g�̍쐬
	m_fadeInState = std::make_unique<FadeInState>(m_fade.get());
	m_fadeOutState = std::make_unique<FadeOutState>(m_fade.get(), FadeOutState::ChageSceneID::SELECT_SCENE);
	m_gameClearMainState = std::make_unique<GameClearMainState>();
	// ���݂̃X�e�[�g��ݒ�
	m_currentState = m_fadeInState.get();

	this->CreateCamera();

	SceneMessenger::GetInstance()->Clear();
	SceneMessenger::GetInstance()->Register(this);
}

void GameClearScene::Start()
{
	// BGM���Đ�����
	m_currentState->PreUpdate();
}

void GameClearScene::Update()
{
	const float deltaTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	m_currentState->Update(deltaTime);

	m_fade->Update();
}

void GameClearScene::Render()
{
	//���f���̕`��
	m_commonResources->GetRenderManager()->Render();
}


void GameClearScene::Finalize()
{

}

void GameClearScene::ChangeState(IState* newState)
{
	// ���㏈��
	m_currentState->PostUpdate();
	// ���݂̃X�e�[�g��؂�ւ���
	m_currentState = newState;
	// ���O����
	m_currentState->PreUpdate();
}

void GameClearScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::FADE_IN:
			this->ChangeState(m_gameClearMainState.get());
			break;
		case Message::FADE_OUT:
			this->ChangeState(m_fadeOutState.get());
			break;
		case Message::MAIN:
			
			break;
		default:
			break;
	}
}

void GameClearScene::CreateCamera()
{
	// �J�����̍쐬
	std::unique_ptr<ICamera> camera = std::make_unique<FixedCamera>(
		DirectX::SimpleMath::Vector3{ 0.0f , 0.0f , 2.0f },
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, DirectX::XMConvertToRadians(45.0f)) *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(-20.0f)));
	camera->Initialize();

	// �J�������}�l�[�W���[�ɐݒ�
	m_commonResources->GetCameraManager()->Attach(std::move(camera));
}