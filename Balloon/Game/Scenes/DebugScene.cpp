// ============================================
// 
// ファイル名: DebugScene.cpp
// 概要: デバッグ用のシーン
// 
// 製作者 : 清水駿希
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
#include "Game/SteeringBehavior/WindBehavior.h"
#include "Game/AmbientLight/AmbientLight.h"
#include "Game/Particle/ParticleEmitter.h"
#include "Game/Factorys/EffectFactory.h"
#include "Game/Message/ObjectMessenger.h"

#include "Game/UIObjects/TitleLogoUI.h"

#include "Game/Factorys/CameraFactory.h"


DebugScene::DebugScene()
{
	m_commonResources  = CommonResources::GetInstance();
	m_parameters       = Parameters::GetInstance();
	m_steeringBehavior = WindBehavior::GetInstance();
	m_root             = Root::GetInstance();
}


DebugScene::~DebugScene()
{

}

void DebugScene::Initialize()
{
	// デバッグカメラ
	m_debugCamera = std::make_unique<DebugCamera>();
	m_debugCamera->Initialize(1280, 720);

	m_root->Initialize();

	

	m_root->Attach(PlayerFactory::CreatePlayer(m_root,
		DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero , DirectX::SimpleMath::Vector3::One * 0.1f));

	m_root->Attach(EnemyFactory::CreateEnemy(m_root,
		DirectX::SimpleMath::Vector3::Backward, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::One * 0.1f));
	
	m_root->Attach(EffectFactory::CreateEffectController(m_root ,{ ParametersID::BALLOON_EXPLOSION, ParametersID::PARTICLE  }));

	std::vector<std::unique_ptr<ICamera>> cameras;
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Backward * 10,
		DirectX::SimpleMath::Quaternion::Identity));
	cameras.emplace_back(CameraFactory::CreateFixedCaemra(
		DirectX::SimpleMath::Vector3::Forward * 5,
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Right , DirectX::XMConvertToRadians(45.0f))));
	cameras.emplace_back(CameraFactory::CreateFollowCaemra(
		ObjectMessenger::GetInstance()->GetObjectI(0)->GetTransform(),
		{0.0f ,8.0f ,8.0f}));

	m_root->Attach(CameraFactory::CreateCameraSystem(m_root, std::move(cameras)));


	/*std::unique_ptr<IObject> logo = std::make_unique<TitleLogoUI>(m_root, nullptr, IObject::ObjectID::NODE_BASE,
		DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One, Message::MessageID::ATTACK);
	logo->Initialize();

	 m_root->Attach(std::move(logo));*/

	ObjectMessenger::GetInstance()->Dispatch(2, { Message::MessageID::BALLOON_EXPLOSION ,0,0.0f ,true });

	ObjectMessenger::GetInstance()->Dispatch(3, { Message::MessageID::BALLOON_EXPLOSION ,2,5.0f ,true });
	//ObjectMessenger::GetInstance()->Dispatch(2, { Message::MessageID::SMOKE ,0,0.0f ,true });

	//m_emitter = std::make_unique< ParticleEmitter>();
	//m_emitter->Initialize(ParametersID::PARTICLE);
	//m_commonResources->GetRenderer()->Attach(m_emitter.get());

	//m_emitter->Play();
}

void DebugScene::Start()
{
	
}

void DebugScene::Update()
{
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// 通知を行う
	KeyboardMessenger::GetInstance()->Dispatch();

	m_steeringBehavior->Update(elapsedTime);

	m_root->Update(elapsedTime);

	// カメラを更新
	/*m_debugCamera->Update();
	m_commonResources->SetViewMatrix(m_debugCamera->GetViewMatrix());*/
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

