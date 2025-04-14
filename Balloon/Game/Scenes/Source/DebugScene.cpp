// ============================================
// 
// ファイル名: DebugScene.cpp
// 概要: デバッグ用のシーン
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Game/Message/ObjectMessenger.h"
#include "Game/Scenes/Header/DebugScene.h"
#include "Interface/IScene.h"
#include "Interface/IObject.h"
#include "Game/Cameras/DebugCamera.h"
#include "Game/Player/Header/Player.h"
#include "Game/Cloud/Cloud.h"

DebugScene::DebugScene()
{
	m_commonResources = CommonResources::GetInstance();
	m_objectMessenger = ObjectMessenger::GetInstance();
}


DebugScene::~DebugScene()
{

}

void DebugScene::Initialize()
{	
	// コモンステート取得
	m_commonStates = m_commonResources->GetCommonStates();

	// デバッグカメラ
	m_debugCamera = std::make_unique<DebugCamera>();
	m_debugCamera->Initialize(1280, 720);

	

	/*m_plaeyr = std::make_unique<Player>(nullptr);
	m_plaeyr->Initialize(IObject::ObjectID::PLAYER, true);
	m_plaeyr->InitialTransform(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180.0f)),
		DirectX::SimpleMath::Vector3::One * 0.1f
	);

	m_cloud = std::make_unique<Cloud>(nullptr);
	m_cloud->Initialize(IObject::ObjectID::CLOUD, true);
	m_cloud->InitialTransform(
		DirectX::SimpleMath::Vector3(-3.0f, -6.0f, 0.0f),
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3(1.3f, 1.0f, 1.3f)
	);

	m_objectMessenger->Register(0, m_plaeyr.get());
	m_objectMessenger->Register(1, m_cloud.get());*/
}

void DebugScene::Start()
{
	// BGMを再生する

	m_commonResources->GetCollisionManager()->Start();
}

void DebugScene::Update()
{
	// カメラを更新
	m_debugCamera->Update();

	//m_plaeyr->Update();

	//m_cloud->Update();
	
	//m_plaeyr->GetTransform()->Update();
	//m_cloud->GetTransform()->Update();
	
}

void DebugScene::Render()
{
	m_commonResources->GetCameraManager()->SetViewMatrix(m_debugCamera->GetViewMatrix());

	/*m_commonResources->GetCollisionManager()->CheckCollision();
	m_commonResources->GetCollisionManager()->Render();*/

	m_commonResources->GetRenderManager()->Render(); 
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
	switch (messageID)
	{
		case Message::FADE_IN:
			break;
		case Message::FADE_OUT:
			break;
		default:
			break;
	}
}

