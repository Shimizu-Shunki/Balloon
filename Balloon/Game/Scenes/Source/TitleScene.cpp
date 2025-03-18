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

	this->Attach<Player>(IObject::ObjectID::PLAYER, true, 
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One * 0.1f, 
		nullptr);

	// �^�C�g�����S�̒ǉ�
	this->Attach<TitleLogo>(IObject::ObjectID::TitleLogoUI, true,
		{ 365.7f , 240.0f , 0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::Zero);
	// �X�^�[�g�̒ǉ�
	this->Attach<StartUI>(IObject::ObjectID::StartUI, true, 
		{ 365.7f , 240.0f + 200.0f , 0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::Zero);

	// �t�F�[�h�̍쐬
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();

	

	// �X�e�[�g�R���g���[���[�̍쐬
	this->CreateStateController();
}

void TitleScene::Start()
{
	// �X�e�[�g�}�V���X�^�[�g����
	m_stateMachine->Start();

	Player* player = this->SearchObject<Player>(IObject::ObjectID::PLAYER);
	StartUI* startUi = this->SearchObject<StartUI>(IObject::ObjectID::StartUI);
	TitleLogo* titleLogoUi = this->SearchObject<TitleLogo>(IObject::ObjectID::TitleLogoUI);

	// �v���C���[��Tween���N��
	player->GetTransform()->GetTween()->
		DORotationY(120.0f, 1.5f).
		SetDelay(3.0f).
		SetEase(Tween::EasingType::EaseInSine);

	// �^�C�g�����S�̃A�j���[�V������ݒ�
	titleLogoUi->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One * 0.5f, 1.0f)
		.SetDelay(4.0f).SetEase(Tween::EasingType::EaseOutBounce);

	// StartUI��Tween���N��
	startUi->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One * 0.6f, 1.0f)
		.SetDelay(4.5f).SetEase(Tween::EasingType::EaseOutBounce);


	// BGM���Đ�
	//m_commonResources->GetAudioManager()->PlayFadeInBgm(XACT_WAVEBANK_SOUNDS_GAMEOVERSCENE, 1.0f);
	// �J������؂�ւ���
	m_commonResources->GetCameraManager()->SwitchActiveCamera(1 , 3.0f , Tween::EasingType::EaseInBack);

	m_commonResources->GetCollisionManager()->Start();
}

void TitleScene::Update()
{
	// �X�e�[�g�}�V���̍X�V
	m_stateMachine->Update();

	m_fade->Update();

	// �I�u�W�F�N�g�̍X�V����
	for (const auto& object : m_objects)
	{
		// object->Update();
	}

	// Transform�̂ݍX�V����
	Player* player = this->SearchObject<Player>(IObject::ObjectID::PLAYER);
	player->GetTransform()->Update();

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

void TitleScene::CreateStateController()
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
	stateController->AddState<FadeOutState>("FadeOutState", m_fade.get(), FadeOutState::ChageSceneID::MENU_SCENE);

	// �f�t�H���g�̃X�e�[�g��ݒ�
	stateController->SetDeffultState("FadeInState");

	// �g�����W�V�����̒ǉ�
	stateController->AddTransition("FadeInState", "TitleMainState", "FadeIN", true);
	stateController->AddTransition("TitleMainState", "FadeOutState", "FadeOUT", true);

	// �X�e�[�g�R���g���[���[��ǉ�
	m_stateMachine->AddController(std::move(stateController));
}

/// <summary>
/// �J�������쐬����
/// </summary>
void TitleScene::CreateCamera()
{
	// �J�����̍쐬
	// �J����1
	std::unique_ptr<ICamera> camera = std::make_unique<FixedCamera>(
		DirectX::SimpleMath::Vector3{ -1.51f,10.44f,-11.57f },
		DirectX::SimpleMath::Quaternion::Identity);
	camera->Initialize();

	// �J�������}�l�[�W���[�ɐݒ�
	m_commonResources->GetCameraManager()->Attach(std::move(camera));

	// �J����2
	camera = std::make_unique<FixedCamera>(
		DirectX::SimpleMath::Vector3{ 1.5f , 1.19f , -2.0f },
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-20.0f)));
	camera->Initialize();
	// �J�������}�l�[�W���[�ɐݒ�
	m_commonResources->GetCameraManager()->Attach(std::move(camera));
}

