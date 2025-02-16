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

#include "Game/Cameras/TPSCamera.h"

// �I�u�W�F�N�g
#include "Game/Cloud/Cloud.h"

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
	m_rootObject.push_back(std::make_unique<Player>(nullptr,nullptr));

	m_rootObject[0]->Initialize(IObject::ObjectID::PLAYER,true);

	// �v���C���[��Transform���q���Ƃ��Đݒ�
	m_rootTransform->SetChild(m_rootObject[0]->GetTransform());
	m_rootObject[0]->GetTransform()->SetLocalPosition({ 0.0f , 11.0f,0.0f });

	

	// �_�̍쐬
	std::unique_ptr<IObject> cloud = std::make_unique<Cloud>(nullptr);
	cloud->Initialize(IObject::ObjectID::CLOUD, true);
	cloud->GetTransform()->SetLocalPosition({ 0.0f , 10.0f,0.0f });
	m_rootTransform->SetChild(cloud->GetTransform());
	// ���[�g�ɓn��
	m_rootObject.push_back(std::move(cloud));

	cloud = std::make_unique<Cloud>(nullptr);
	cloud->Initialize(IObject::ObjectID::CLOUD, true);
	cloud->GetTransform()->SetLocalPosition({ -20.0f , 8.0f,20.0f });
	m_rootTransform->SetChild(cloud->GetTransform());
	// ���[�g�ɓn��
	m_rootObject.push_back(std::move(cloud));

	cloud = std::make_unique<Cloud>(nullptr);
	cloud->Initialize(IObject::ObjectID::CLOUD, true);
	cloud->GetTransform()->SetLocalPosition({ 20.0f , 8.0f, 20.0f });
	m_rootTransform->SetChild(cloud->GetTransform());
	// ���[�g�ɓn��
	m_rootObject.push_back(std::move(cloud));

	cloud = std::make_unique<Cloud>(nullptr);
	cloud->Initialize(IObject::ObjectID::CLOUD, true);
	cloud->GetTransform()->SetLocalPosition({ -20.0f , 8.0f,-20.0f });
	m_rootTransform->SetChild(cloud->GetTransform());
	// ���[�g�ɓn��
	m_rootObject.push_back(std::move(cloud));

	cloud = std::make_unique<Cloud>(nullptr);
	cloud->Initialize(IObject::ObjectID::CLOUD, true);
	cloud->GetTransform()->SetLocalPosition({ 20.0f , 8.0f,-20.0f });
	m_rootTransform->SetChild(cloud->GetTransform());
	// ���[�g�ɓn��
	m_rootObject.push_back(std::move(cloud));

	// �J�����̍쐬
	// �J����1
	/* m_camera = std::make_unique<TPSCamera>(m_rootObject[0].get());
	m_camera->Initialize({ -1.51f,10.44f,-11.57f }, { 0.0f,0.0f,0.0f },
		DirectX::SimpleMath::Quaternion::Identity, m_commonResources->GetCameraManager());*/

	// �J�������}�l�[�W���[�ɐݒ�
	//m_commonResources->GetCameraManager()->Attach(std::move(camera));

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
