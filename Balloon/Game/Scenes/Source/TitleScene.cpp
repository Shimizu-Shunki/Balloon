#include "Framework/pch.h"
#include "Game/Scenes/Header/TitleScene.h"
// フレームワーク
#include "Framework/CommonResources.h"
#include "Framework/RenderManager.h"
#include "Framework/Tween/Tween.h"
#include "Game/Message/SceneMessenger.h"
// インターフェース
#include "Interface/IScene.h"
#include "Interface/IObject.h"
// オブジェクト
#include "Game/Player/Header/Player.h"
#include "Game/Fade/Fade.h"
// カメラ
#include "Game/Cameras/FixedCamera.h"
#include "Game/Cameras/DebugCamera.h"
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

	this->Attach<Player>(IObject::ObjectID::PLAYER, true, 
		DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One * 0.1f, 
		nullptr);

	// タイトルロゴの追加
	this->Attach<TitleLogo>(IObject::ObjectID::TitleLogoUI, true,
		{ 365.7f , 240.0f , 0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::Zero);
	// スタートの追加
	this->Attach<StartUI>(IObject::ObjectID::StartUI, true, 
		{ 365.7f , 240.0f + 200.0f , 0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::Zero);

	// フェードの作成
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();

	SceneMessenger::GetInstance()->Clear();
	SceneMessenger::GetInstance()->Register(this);

	// ステートコントローラーの作成
	this->CreateStateController();
}

void TitleScene::Start()
{
	// ステートマシンスタート処理
	m_currentState->PreUpdate();

	Player* player         = this->SearchObject<Player>(IObject::ObjectID::PLAYER);
	StartUI* startUi       = this->SearchObject<StartUI>(IObject::ObjectID::StartUI);
	TitleLogo* titleLogoUi = this->SearchObject<TitleLogo>(IObject::ObjectID::TitleLogoUI);

	// プレイヤーのTweenを起動
	player->GetTransform()->GetTween()->
		DORotationY(120.0f, 1.5f).
		SetDelay(3.0f).
		SetEase(Tween::EasingType::EaseInSine);

	// タイトルロゴのアニメーションを設定
	titleLogoUi->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One * 0.5f, 1.0f)
		.SetDelay(4.0f).SetEase(Tween::EasingType::EaseOutBounce);
	// StartUIのTweenを起動
	startUi->GetTransform()->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One * 0.6f, 1.0f)
		.SetDelay(4.5f).SetEase(Tween::EasingType::EaseOutBounce);


	// BGMを再生
	//m_commonResources->GetAudioManager()->PlayFadeInBgm(XACT_WAVEBANK_SOUNDS_GAMEOVERSCENE, 1.0f);
	// カメラを切り替える
	m_commonResources->GetCameraManager()->SwitchActiveCamera(1 , 3.0f , Tween::EasingType::EaseInBack);

	m_commonResources->GetCollisionManager()->Start();
}

void TitleScene::Update()
{
	const float deltaTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// 現在のステートを更新
	m_currentState->Update(deltaTime);

	// オブジェクトの更新処理
	for (const auto& object : m_objects)
	{
		// object->Update();
	}

	// Transformのみ更新する
	Player* player = this->SearchObject<Player>(IObject::ObjectID::PLAYER);
	player->GetTransform()->Update();

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
	// ステートの作成
	m_fadeInState = std::make_unique<FadeInState>(m_fade.get());
	m_fadeOutState = std::make_unique<FadeOutState>(m_fade.get(), FadeOutState::ChageSceneID::MENU_SCENE);
	m_titleMainState = std::make_unique<TitleMainState>();
	// 現在のステートを設定
	m_currentState = m_fadeInState.get();
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


void TitleScene::ChangeState(IState* newState)
{
	// 事後処理
	m_currentState->PostUpdate();
	// 現在のステートを切り替える
	m_currentState = newState;
	// 事前処理
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
