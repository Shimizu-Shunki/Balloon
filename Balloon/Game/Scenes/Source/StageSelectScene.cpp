// ============================================
// 
// �t�@�C����: StageSelectScene.cpp
// �T�v: �X�e�[�W�Z���N�g�V�[��
//  
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Scenes/Header/StageSelectScene.h"
// �t���[�����[�N
#include "Framework/CommonResources.h"
#include "Framework/RenderManager.h"
#include "Framework/Tween/Tween.h"
#include "Game/Message/SceneMessenger.h"
// �C���^�[�t�F�[�X
#include "Interface/IScene.h"
#include "Interface/IObject.h"
// �I�u�W�F�N�g
#include "Game/Player/Header/Player.h"
#include "Game/Fade/Fade.h"
// �J����
#include "Game/Cameras/FixedCamera.h"
#include "Game/Cameras/DebugCamera.h"
// UI
#include "Game/UI/TitleLogo.h"
#include "Game/UI/CloudFrame.h"
#include "Game/UI/StageSelectText.h"
#include "Game/UI/StageNumberUI.h"
#include "Game/UI/StageSelectKeyGuide.h"

// �X�e�[�g
#include "Game/States/Fade/FadeInState.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/States/StageSelectScene/StageSelectMainState.h"

StageSelectScene::StageSelectScene()
{
	m_commonResources = CommonResources::GetInstance();
}


StageSelectScene::~StageSelectScene()
{

}

void StageSelectScene::Initialize()
{
	// �J�����̍쐬
	this->CreateCamera();

	// �_�t���[��
	for (int i = 0; i < 6; i++)
	{
		this->Attach<CloudFrame>(IObject::ObjectID::CLOUD_FRAME_UI, true,
			{ (1280.0f / 2.0f)/* - (1280.0f / 1.5f)*/ + (1280.0f / 1.5f) * i , 720.0f / 2.0f , 0.0f },
			DirectX::SimpleMath::Quaternion::Identity,
			DirectX::SimpleMath::Vector3::One * 0.7f , i + 1);
	}

	// �X�e�[�W�Z���N�g�e�L�X�g
	this->Attach<StageSelectText>(IObject::ObjectID::STAGE_SELECT_TEXT_UI, true,
		{260.0f , 70.0f , 0.0f},
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One * 0.5f);

	// �X�e�[�W�Z���N�g�L�[�K�C�h
	this->Attach<StageSelectKeyGuide>(IObject::ObjectID::STAGE_SELECT_KEY_GUIDE, true,
		{ 1280.0f / 2.0f - 30.0f , 676.0f , 0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One * 0.65f);

	// �v���C���[
	this->Attach<Player>(IObject::ObjectID::PLAYER, true,
		{40.0f , 3.0f , 4.0f},
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up,DirectX::XMConvertToRadians(180.0f)),
		DirectX::SimpleMath::Vector3::One * 0.1f,
		nullptr);


	// �t�F�[�h�̍쐬
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();

	SceneMessenger::GetInstance()->Clear();
	SceneMessenger::GetInstance()->Register(this);

	// �X�e�[�g�R���g���[���[�̍쐬
	this->CreateStateController();
}

void StageSelectScene::Start()
{
	// BGM���Đ�
	m_commonResources->GetAudioManager()->PlayFadeInBgm(XACT_WAVEBANK_SOUNDS_GAMEOVERSCENE, 1.0f);

	// �X�e�[�g�}�V���X�^�[�g����
	m_currentState->PreUpdate();

	// Tween��ݒ�
	Player* player = this->SearchObject<Player>(IObject::ObjectID::PLAYER);
	player->GetTransform()->GetTween()->DOMoveX(-40.0f, 20.0f).SetLoops(100, Tween::LoopType::Restart);
	player->GetTransform()->GetTween()->DORotationY(10.0f, 2.0f).SetLoops(100, Tween::LoopType::Increment);
	
	// BGM���Đ�
	// m_commonResources->GetAudioManager()->PlayFadeInBgm(XACT_WAVEBANK_SOUNDS_GAMEOVERSCENE, 1.0f);

	m_commonResources->GetCollisionManager()->Start();
}

void StageSelectScene::Update()
{
	const float deltaTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// ���݂̃X�e�[�g���X�V
	m_currentState->Update(deltaTime);

	// �I�u�W�F�N�g�̍X�V����
	//for (const auto& object : m_objects)
	//{
	//	// object->Update();
	//}

	// Transform�̂ݍX�V����
	Player* player = this->SearchObject<Player>(IObject::ObjectID::PLAYER);
	player->GetTransform()->Update();

}

void StageSelectScene::Render()
{
	m_commonResources->GetCollisionManager()->CheckCollision();
	m_commonResources->GetCollisionManager()->Render();
	//���f���̕`��
	m_commonResources->GetRenderManager()->Render();

}


void StageSelectScene::Finalize()
{

}

void StageSelectScene::CreateStateController()
{
	// �X�e�[�g�̍쐬
	m_fadeInState          = std::make_unique<FadeInState>(m_fade.get());
	m_fadeOutState         = std::make_unique<FadeOutState>(m_fade.get(), FadeOutState::ChageSceneID::PLAY_SCENE);
	m_stageSelectMainState = std::make_unique<StageSelectMainState>();
	// ���݂̃X�e�[�g��ݒ�
	m_currentState = m_fadeInState.get();
}

/// <summary>
/// �J�������쐬����
/// </summary>
void StageSelectScene::CreateCamera()
{
	// �J�����̍쐬
	std::unique_ptr<ICamera> camera = std::make_unique<FixedCamera>(
		DirectX::SimpleMath::Vector3{ 0.0f , 2.0f , -2.0f },
		DirectX::SimpleMath::Quaternion::Identity);
	camera->Initialize();

	// �J�������}�l�[�W���[�ɐݒ�
	m_commonResources->GetCameraManager()->Attach(std::move(camera));
}


void StageSelectScene::ChangeState(IState* newState)
{
	// ���㏈��
	m_currentState->PostUpdate();
	// ���݂̃X�e�[�g��؂�ւ���
	m_currentState = newState;
	// ���O����
	m_currentState->PreUpdate();
}

void StageSelectScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::FADE_IN:
			this->ChangeState(m_stageSelectMainState.get());
			break;
		case Message::FADE_OUT:
			this->ChangeState(m_fadeOutState.get());
			break;
		case Message::FADE_OUT_MENU_SCENE:
			// ID��ύX
			dynamic_cast<FadeOutState*>(m_fadeOutState.get())->SetSceneID(FadeOutState::ChageSceneID::MENU_SCENE);
			// �X�e�[�g��ύX
			this->ChangeState(m_fadeOutState.get());
			break;
		case Message::MAIN:
			this->ChangeState(m_stageSelectMainState.get());
		default:
			break;
	}
}
