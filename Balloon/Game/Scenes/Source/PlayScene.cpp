#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Framework/RenderManager.h"
#include "Game/Scenes/Header/PlayScene.h"
#include "Interface/IScene.h"
#include "Interface/IObject.h"
#include "Framework/Tween/Tween.h"

#include "Game/Player/Header/Player.h"

#include "Game/Cameras/DebugCamera.h"

#include "Game/Fade/Fade.h"
#include "Game/Jump/Jump.h"
#include "Framework/CollisionManager.h"

#include "Game/Cameras/TPSKeyCamera.h"

// �I�u�W�F�N�g
#include "Game/Cloud/Cloud.h"
#include "Game/Enemy/Enemy.h"

// �X�e�[�g
#include "Framework/StateMachine/StateController.h"
#include "Framework/StateMachine/StateMachine.h"
#include "Game/States/Fade/FadeInState.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/States/PlayScene/PlayMainState.h"


PlayScene::PlayScene()
{
	m_commonResources = CommonResources::GetInstance();
}


PlayScene::~PlayScene()
{

}

void PlayScene::Initialize()
{
	// �f�o�b�O�J����
	m_debugCamera = std::make_unique<DebugCamera>();
	m_debugCamera->Initialize(1280, 720);

	// Transform���쐬
	m_rootTransform = std::make_unique<Transform>(); 

	// �e�����Ȃ��̂�nullptr��ݒ�
	m_rootTransform->SetParent(nullptr);
	// �v���C���[�̍쐬
	m_rootObject.push_back(std::make_unique<Player>(nullptr));

	m_rootObject[0]->Initialize(IObject::ObjectID::PLAYER,true);
	m_rootObject[0]->InitialTransform(
		DirectX::SimpleMath::Vector3(0.0f, 11.0f, 0.0f),
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180.0f)),
		DirectX::SimpleMath::Vector3::One * 0.1f
	);
	m_rootObject[0]->GetTransform()->SetParent(m_rootTransform.get());


	std::unique_ptr<IObject> enemy = std::make_unique<Enemy>(nullptr);
	enemy->Initialize(IObject::ObjectID::ENEMY, true);
	enemy->InitialTransform(
		DirectX::SimpleMath::Vector3(0.0f, 11.0f, -3.0f),
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180.0f)),
		DirectX::SimpleMath::Vector3::One * 0.1f
	);
	enemy->GetTransform()->SetParent(m_rootTransform.get());
	m_rootObject.push_back(std::move(enemy));

	// �_�̍쐬
	std::unique_ptr<IObject> cloud = std::make_unique<Cloud>(nullptr);
	cloud->Initialize(IObject::ObjectID::CLOUD, true);
	cloud->InitialTransform(
		DirectX::SimpleMath::Vector3(0.0f, 10.0f, 0.0f),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(1.0f, 0.3f, 1.0f)
	);
	cloud->GetTransform()->SetParent(m_rootTransform.get());
	// ���[�g�ɓn��
	m_rootObject.push_back(std::move(cloud));

	cloud = std::make_unique<Cloud>(nullptr);
	cloud->Initialize(IObject::ObjectID::CLOUD, true);
	cloud->InitialTransform(
		DirectX::SimpleMath::Vector3(-20.0f, 8.0f, 20.0f),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(1.0f, 0.3f, 1.0f)
	);
	cloud->GetTransform()->SetParent(m_rootTransform.get());
	// ���[�g�ɓn��
	m_rootObject.push_back(std::move(cloud));

	cloud = std::make_unique<Cloud>(nullptr);
	cloud->Initialize(IObject::ObjectID::CLOUD, true);
	cloud->InitialTransform(
		DirectX::SimpleMath::Vector3(20.0f, 8.0f, 20.0f),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(1.0f, 0.3f, 1.0f)
	);
	cloud->GetTransform()->SetParent(m_rootTransform.get());
	// ���[�g�ɓn��
	m_rootObject.push_back(std::move(cloud));

	cloud = std::make_unique<Cloud>(nullptr);
	cloud->Initialize(IObject::ObjectID::CLOUD, true);
	cloud->InitialTransform(
		DirectX::SimpleMath::Vector3(-20.0f, 8.0f, -20.0f),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(1.0f, 0.3f, 1.0f)
	);
	cloud->GetTransform()->SetParent(m_rootTransform.get());
	// ���[�g�ɓn��
	m_rootObject.push_back(std::move(cloud));

	cloud = std::make_unique<Cloud>(nullptr);
	cloud->Initialize(IObject::ObjectID::CLOUD, true);
	cloud->InitialTransform(
		DirectX::SimpleMath::Vector3(20.0f, 8.0f, -20.0f),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(1.0f, 0.3f, 1.0f)
	);
	cloud->GetTransform()->SetParent(m_rootTransform.get());
	// ���[�g�ɓn��
	m_rootObject.push_back(std::move(cloud));

	

	//m_commonResources->GetCameraManager()->ChageCamera(2);

	// �t�F�[�h�̍쐬
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();

	this->CreateStateStateController();

}

void PlayScene::Start()
{
	m_stateMachine->Start();
	// BGM���Đ�
	//m_commonResources->GetAudioManager()->PlayFadeInBgm(XACT_WAVEBANK_SOUNDS_PLAYSCENE, 3.0f);

	m_commonResources->GetCollisionManager()->Start();
}

void PlayScene::Update()
{
	m_stateMachine->Update();

	//m_camera->Update();


	for (const auto& object : m_rootObject)
	{
		object->Update();
	}

	m_rootTransform->Update();

	m_debugCamera->Update();
	m_commonResources->GetCameraManager()->SetViewMatrix(m_debugCamera->GetViewMatrix());

	m_fade->Update();
}

void PlayScene::Render()
{
	m_commonResources->GetCollisionManager()->CheckCollision();
	m_commonResources->GetCollisionManager()->Render();

	//���f���̕`��
	m_commonResources->GetRenderManager()->Render();
}


void PlayScene::Finalize()
{

}

void PlayScene::CreateStateStateController()
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
	stateController->AddState<PlayMainState>("PlayMainState");
	stateController->AddState<FadeOutState>("FadeOutState", m_fade.get(), FadeOutState::ChageSceneID::TITLE_SCENE);

	// �f�t�H���g�̃X�e�[�g��ݒ�
	stateController->SetDeffultState("FadeInState");

	// �g�����W�V�����̒ǉ�
	stateController->AddTransition("FadeInState", "PlayMainState", "FadeIN", true);
	stateController->AddTransition("PlayMainState", "FadeOutState", "FadeOUT", true);

	// �X�e�[�g�R���g���[���[��ǉ�
	m_stateMachine->AddController(std::move(stateController));
}
