#include "Framework/pch.h"
#include "Game/Scenes/Header/TitleScene.h"
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

	SceneMessenger::GetInstance()->Clear();
	SceneMessenger::GetInstance()->Register(this);

	// �X�e�[�g�R���g���[���[�̍쐬
	this->CreateStateController();
}

void TitleScene::Start()
{
	// �X�e�[�g�}�V���X�^�[�g����
	m_currentState->PreUpdate();

	Player* player         = this->SearchObject<Player>(IObject::ObjectID::PLAYER);
	StartUI* startUi       = this->SearchObject<StartUI>(IObject::ObjectID::StartUI);
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
	const float deltaTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// ���݂̃X�e�[�g���X�V
	m_currentState->Update(deltaTime);

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
	// �X�e�[�g�̍쐬
	m_fadeInState = std::make_unique<FadeInState>(m_fade.get());
	m_fadeOutState = std::make_unique<FadeOutState>(m_fade.get(), FadeOutState::ChageSceneID::MENU_SCENE);
	m_titleMainState = std::make_unique<TitleMainState>();
	// ���݂̃X�e�[�g��ݒ�
	m_currentState = m_fadeInState.get();
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


void TitleScene::ChangeState(IState* newState)
{
	// ���㏈��
	m_currentState->PostUpdate();
	// ���݂̃X�e�[�g��؂�ւ���
	m_currentState = newState;
	// ���O����
	m_currentState->PreUpdate();
}

void TitleScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::FADE_IN:
			break;
		case Message::FADE_OUT:
			this->ChangeState(m_fadeOutState.get());
			break;
		case Message::MAIN:
			this->ChangeState(m_titleMainState.get());
		default:
			break;
	}
}
