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


// ステート
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
	// カメラの作成
	this->CreateCamera();

	// オブジェクト
	m_player = std::make_unique<Player>(nullptr);
	m_player->Initialize(IObject::ObjectID::PLAYER , true);
	m_player->InitialTransform(
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One * 0.1f
	);

	// プレイヤーのTweenを起動
	m_player->GetTransform()->GetTween()->DORotationY(120.0f, 1.5f).SetDelay(4.0f).SetEase(Tween::EasingType::EaseInSine);

	// UI
	// タイトルロゴ
	m_titleLogo = std::make_unique<TitleLogo>();
	m_titleLogo->Initialize(IObject::ObjectID::PLAYER, true);




	// フェードの作成
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();

	// ステートコントローラーの作成
	this->CreateStateController();
}

void TitleScene::Start()
{
	// ステートマシンスタート処理
	m_stateMachine->Start();
	// BGMを再生
	//m_commonResources->GetAudioManager()->PlayFadeInBgm(XACT_WAVEBANK_SOUNDS_GAMEOVERSCENE, 1.0f);
	// カメラを切り替える
	m_commonResources->GetCameraManager()->SwitchActiveCamera(1 , 3.0f , Tween::EasingType::EaseInBack);

	m_commonResources->GetCollisionManager()->Start();
}

void TitleScene::Update()
{
	// ステートマシンの更新
	m_stateMachine->Update();

	m_fade->Update();




	m_player->GetTransform()->Update();
}

void TitleScene::Render()
{
	m_commonResources->GetCollisionManager()->CheckCollision();
	m_commonResources->GetCollisionManager()->Render();
	//モデルの描画
	m_commonResources->GetRenderManager()->Render();

}


void TitleScene::Finalize()
{

}

void TitleScene::CreateStateController()
{
	// ステートマシーンの作成
	m_stateMachine = std::make_unique<StateMachine>();

	// ステートコントローラーの作成
	auto stateController = std::make_unique<StateController>();

	// パラメーターの追加
	stateController->AddParameters("FadeIN", false);
	stateController->AddParameters("FadeOUT", false);

	// ステートの追加
	stateController->AddState<FadeInState>("FadeInState", m_fade.get());
	stateController->AddState<TitleMainState>("TitleMainState");
	stateController->AddState<FadeOutState>("FadeOutState", m_fade.get(), FadeOutState::ChageSceneID::PLAY_SCENE);

	// デフォルトのステートを設定
	stateController->SetDeffultState("FadeInState");

	// トランジションの追加
	stateController->AddTransition("FadeInState", "TitleMainState", "FadeIN", true);
	stateController->AddTransition("TitleMainState", "FadeOutState", "FadeOUT", true);

	// ステートコントローラーを追加
	m_stateMachine->AddController(std::move(stateController));
}

/// <summary>
/// カメラを作成する
/// </summary>
void TitleScene::CreateCamera()
{
	// カメラの作成
	// カメラ1
	std::unique_ptr<ICamera> camera = std::make_unique<FixedCamera>(
		DirectX::SimpleMath::Vector3{ -1.51f,10.44f,-11.57f },
		DirectX::SimpleMath::Quaternion::Identity);
	camera->Initialize();

	// カメラをマネージャーに設定
	m_commonResources->GetCameraManager()->Attach(std::move(camera));

	// カメラ2
	camera = std::make_unique<FixedCamera>(
		DirectX::SimpleMath::Vector3{ 1.5f , 1.19f , -2.0f },
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-20.0f)));
	camera->Initialize();
	// カメラをマネージャーに設定
	m_commonResources->GetCameraManager()->Attach(std::move(camera));
}

