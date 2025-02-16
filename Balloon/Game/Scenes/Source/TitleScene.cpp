#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Framework/RenderManager.h"
#include "Game/Scenes/Header/TitleScene.h"
#include "Interface/IScene.h"
#include "Interface/IObject.h"

#include "Game/Player/Header/Player.h"
#include "Framework/StateMachine/StateMachine.h"
#include "Framework/StateMachine/StateController.h"

#include "Game/Cameras/FixedCamera.h"
#include "Game/Fade/Fade.h"

#include "Game/Cameras/DebugCamera.h"

#include "Framework/Tween/Tween.h"
#include "Game/Scenes/Header/PlayScene.h"

// UI
#include "Game/UI/TitleLogo.h"
#include "Game/UI/Text.h"
#include "Game/UI/Keys.h"

// �X�e�[�g
#include "Game/States/Fade/FadeInState.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/States/TitleScene/TitleMainState.h"

TitleScene::TitleScene()
{
	m_commonResources = CommonResources::GetInstance();
}


TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	// �J�����̍쐬
	this->CreateCamera();

	// �I�u�W�F�N�g
	m_player = std::make_unique<Player>(nullptr, nullptr);
	m_player->Initialize(IObject::ObjectID::PLAYER,true);

	// �v���C���[�̏�����]�p��ݒ�
	m_player->GetTransform()->SetLocalRotation(
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f))
	);
	// �v���C���[��Tween���N��
	m_player->GetTransform()->GetTween()->DORotationY(120.0f, 1.5f).SetDelay(4.0f).SetEase(Tween::EasingType::EaseInSine);

	// UI
	// �^�C�g�����S
	m_titleLogo = std::make_unique<TitleLogo>();
	m_titleLogo->Initialize();
	// �X�y�[�X�L�[
	m_text = std::make_unique<Text>();
	m_text->Initialize();
	// �X�^�[�g�e�L�X�g
	m_spaceKey = std::make_unique<Keys>();
	m_spaceKey->Initialize();

	// �t�F�[�h�̍쐬
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();

	// �X�e�[�g�R���g���[���[�̍쐬
	this->CreateStateStateController();
}

void TitleScene::Start()
{
	// �X�e�[�g�}�V���X�^�[�g����
	m_stateMachine->Start();
	// BGM���Đ�
	//m_commonResources->GetAudioManager()->PlayFadeInBgm(XACT_WAVEBANK_SOUNDS_GAMEOVERSCENE, 1.0f);
	// �J������؂�ւ���
	m_commonResources->GetCameraManager()->SwitchActiveCamera(1);

	m_commonResources->GetCollisionManager()->Start();
}

void TitleScene::Update()
{
	// �X�e�[�g�}�V���̍X�V
	m_stateMachine->Update();

	m_fade->Update();

	m_titleLogo->Update();
	m_text->Update();
	m_spaceKey->Update();

	m_player->GetTransform()->Update();
}

void TitleScene::Render()
{
	m_commonResources->GetCollisionManager()->CheckCollision();
	m_commonResources->GetCollisionManager()->Render();
	//���f���̕`��
	m_commonResources->GetRenderManager()->Render();

}


void TitleScene::Finalize()
{

}

void TitleScene::CreateStateStateController()
{
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
	stateController->AddState<FadeOutState>("FadeOutState", m_fade.get(), FadeOutState::ChageSceneID::PLAY_SCENE);

	// �f�t�H���g�̃X�e�[�g��ݒ�
	stateController->SetDeffultState("FadeInState");

	// �g�����W�V�����̒ǉ�
	stateController->AddTransition("FadeInState", "TitleMainState", "FadeIN", true);
	stateController->AddTransition("TitleMainState", "FadeOutState", "FadeOUT", true);

	// �X�e�[�g�R���g���[���[��ǉ�
	m_stateMachine->AddController(std::move(stateController));
}

void TitleScene::CreateCamera()
{
	// �J�����̍쐬
	// �J����1
	std::unique_ptr<ICamera> camera = std::make_unique<FixedCamera>();
	camera->Initialize({ -1.51f,10.44f,-11.57f }, { 0.0f,0.0f,0.0f },
		DirectX::SimpleMath::Quaternion::Identity, m_commonResources->GetCameraManager());

	// �J�������}�l�[�W���[�ɐݒ�
	m_commonResources->GetCameraManager()->Attach(std::move(camera));

	// �J����2
	camera = std::make_unique<FixedCamera>();
	camera->Initialize({ 1.5f,1.19f,-2.0f }, { 0.0f,0.0f,0.0f },
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-20.0f)),
		m_commonResources->GetCameraManager());

	// �J�������}�l�[�W���[�ɐݒ�
	m_commonResources->GetCameraManager()->Attach(std::move(camera));
}

