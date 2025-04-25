// ============================================
// 
// �t�@�C����: DebugScene.cpp
// �T�v: �f�o�b�O�p�̃V�[��
// 
// ����� : �����x��
// 
// ============================================
#include "pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/DebugScene.h"
#include "Interface/IObject.h"
#include "Interface/IScene.h"
#include "Game/Cameras/DebugCamera.h"
#include "Game/Node/Root.h"
#include "Game/Factorys/PlayerFactory.h"
#include "Game/Factorys/EnemyFactory.h"
#include "Game/Message/KeyboardMessenger.h"
#include "Game/Parameters/Parameters.h"


DebugScene::DebugScene()
{
	m_commonResources = CommonResources::GetInstance();
	m_parameters = Parameters::GetInstance();
}


DebugScene::~DebugScene()
{

}

void DebugScene::Initialize()
{
	// �f�o�b�O�J����
	m_debugCamera = std::make_unique<DebugCamera>();
	m_debugCamera->Initialize(1280, 720);

	m_root = std::make_unique<Root>(nullptr, IObject::ObjectID::NODE_BASE,
		DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One
	);
	m_root->Initialize();

	m_root->Attach(PlayerFactory::CreatePlayer(m_root.get(),
		DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Up * 180.0f, DirectX::SimpleMath::Vector3::One * 0.1f));

	m_root->Attach(EnemyFactory::CreateEnemy(m_root.get(),
		DirectX::SimpleMath::Vector3::Backward, DirectX::SimpleMath::Vector3::Up * 180.0f, DirectX::SimpleMath::Vector3::One * 0.1f));
}

void DebugScene::Start()
{
	
}

void DebugScene::Update()
{
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// �ʒm���s��
	KeyboardMessenger::GetInstance()->Dispatch();

	// �J�������X�V
	m_debugCamera->Update();
	m_commonResources->SetViewMatrix(m_debugCamera->GetViewMatrix());

	m_root->Update(elapsedTime);
}

void DebugScene::Render()
{
	m_commonResources->GetRenderer()->Render();
}


void DebugScene::Finalize()
{

}

void DebugScene::ChangeState(IState* newState)
{
	(void)newState;
}

void DebugScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	(void)messageID;
}

