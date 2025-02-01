#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Framework/RenderManager.h"
#include "Game/Scenes/Header/PlayScene.h"
#include "Interface/IScene.h"
#include "Interface/IObject.h"
#include "Framework/Tween/Tween.h"

#include "Game/Player/Header/Player.h"

#include "Game/Cameras/DebugCamera.h"

PlayScene::PlayScene()
{
	m_commonResources = CommonResources::GetInstance();
}


PlayScene::~PlayScene()
{

}

void PlayScene::Initialize()
{
	// デバッグカメラ
	m_debugCamera = std::make_unique<DebugCamera>();
	m_debugCamera->Initialize(1280, 720);

	// Transformを作成
	m_rootTransform = std::make_unique<Transform>();

	// 親がいないのでnullptrを設定
	m_rootTransform->SetParent(nullptr);
	// プレイヤーの作成
	m_rootObject.push_back(std::make_unique<Player>(nullptr,nullptr));

	m_rootObject[0]->Initialize(IObject::ObjectID::PLAYER,true);

	// プレイヤーのTransformを子供として設定
	m_rootTransform->SetChild(m_rootObject[0]->GetTransform());
}

void PlayScene::Start()
{
	// Tweenテスト
	m_rootObject[0]->GetTransform()->GetTween()->DORotation({ 0.0f,30.0f,30.0f }, 4.0f).SetEase(Tween::EasingType::EaseInBounce);
}

void PlayScene::Update()
{
	m_rootObject[0]->Update();

	m_rootTransform->Update();

	m_debugCamera->Update();
	m_commonResources->GetCameraManager()->SetViewMatrix(m_debugCamera->GetViewMatrix());
}

void PlayScene::Render()
{
	//モデルの描画
	m_commonResources->GetRenderManager()->Render();
}


void PlayScene::Finalize()
{

}

