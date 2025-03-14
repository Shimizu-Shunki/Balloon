#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/Header/DebugScene.h"
#include "Interface/IScene.h"
#include "Interface/IObject.h"
#include "Game/Cameras/DebugCamera.h"
#include "Game/Player/Header/Player.h"

DebugScene::DebugScene()
{
	m_commonResources = CommonResources::GetInstance();
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

	

	m_plaeyr = std::make_unique<Player>(nullptr);
	m_plaeyr->Initialize(IObject::ObjectID::PLAYER, true);
	m_plaeyr->InitialTransform(
		DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180.0f)),
		DirectX::SimpleMath::Vector3::One * 0.1f
	);

	m_plaeyr->GetTransform()->Update();
}

void DebugScene::Start()
{
	// BGMを再生する
}

void DebugScene::Update()
{
	// カメラを更新
	m_debugCamera->Update();

	m_plaeyr->Update();
	

	
}

void DebugScene::Render()
{
	m_commonResources->GetCameraManager()->SetViewMatrix(m_debugCamera->GetViewMatrix());
	m_commonResources->GetRenderManager()->Render();
}


void DebugScene::Finalize()
{

}

