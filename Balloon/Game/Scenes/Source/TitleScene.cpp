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
#include "Game/UI/TitleLogo.h"
#include "Framework/Tween/Tween.h"
#include "Game/Scenes/Header/PlayScene.h"

TitleScene::TitleScene()
{
	m_commonResources = CommonResources::GetInstance();
}


TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	// ステートマシーンの作成
	m_stateMachine = std::make_unique<StateMachine>();

	// カメラの作成
	// カメラ1
	std::unique_ptr<ICamera> camera = std::make_unique<FixedCamera>();
	camera->Initialize({ -1.51f,10.44f,-11.57f }, { 0.0f,0.0f,0.0f }, 
		DirectX::SimpleMath::Quaternion::Identity, m_commonResources->GetCameraManager());
	// カメラをマネージャーに設定
	m_commonResources->GetCameraManager()->Attach(std::move(camera));
	// カメラ2
	camera = std::make_unique<FixedCamera>();
	camera->Initialize({ 1.5f,1.19f,-2.0f }, { 0.0f,0.0f,0.0f }, 
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY,DirectX::XMConvertToRadians(-20.0f)), m_commonResources->GetCameraManager());
	// カメラをマネージャーに設定
	m_commonResources->GetCameraManager()->Attach(std::move(camera));

	m_titleLogo = std::make_unique<TitleLogo>();
	m_titleLogo->Initialize();

	m_player = std::make_unique<Player>(nullptr, nullptr);
	m_player->Initialize(IObject::ObjectID::PLAYER,true);

	m_player->GetTransform()->SetLocalRotation(
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f))
	);

	m_player->GetTransform()->GetTween()->DORotationY(120.0f, 1.5f).SetDelay(4.0f).SetEase(Tween::EasingType::EaseInSine);

	//m_player->GetTransform()->SetLocalScale()

	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();

	
	


	// スプライトの追加
	//m_commonResources->GetRenderManager()->AddSprite(m_titleLogo.get());

	// ステートコントローラーの作成
	auto stateController = std::make_unique<StateController>(true);

	// パラメーターの追加
	stateController->AddParameters("Main", false);
	stateController->AddParameters("FadeIN", 0);

	// ステートの追加

	// トランジションの追加


}

void TitleScene::Start()
{
	// BGMを再生する
	m_fade->FadeIN(1.5f);

	m_commonResources->GetAudioManager()->PlayFadeInBgm(XACT_WAVEBANK_SOUNDS_GAMEOVERSCENE, 1.0f);

	m_commonResources->GetCameraManager()->ChageCamera(1);
}

void TitleScene::Update()
{
	m_fade->Update();

	m_titleLogo->Update();

	m_player->GetTransform()->Update();
}

void TitleScene::Render()
{
	//モデルの描画
	m_commonResources->GetRenderManager()->Render();

}


void TitleScene::Finalize()
{

}

