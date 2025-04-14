// ============================================
// 
// ファイル名: StageSelectScene.cpp
// 概要: ステージセレクトシーン
//  
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Scenes/Header/StageSelectScene.h"
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
#include "Game/UI/CloudFrame.h"
#include "Game/UI/StageSelectText.h"
#include "Game/UI/StageNumberUI.h"
#include "Game/UI/StageSelectKeyGuide.h"

// ステート
#include "Game/States/Fade/FadeInState.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/States/StageSelectScene/StageSelectMainState.h"

StageSelectScene::StageSelectScene()
{
	m_commonResources = CommonResources::GetInstance();
}


StageSelectScene::~StageSelectScene()
{

}

void StageSelectScene::Initialize()
{
	// カメラの作成
	this->CreateCamera();

	// 雲フレーム
	for (int i = 0; i < 6; i++)
	{
		this->Attach<CloudFrame>(IObject::ObjectID::CLOUD_FRAME_UI, true,
			{ (1280.0f / 2.0f)/* - (1280.0f / 1.5f)*/ + (1280.0f / 1.5f) * i , 720.0f / 2.0f , 0.0f },
			DirectX::SimpleMath::Quaternion::Identity,
			DirectX::SimpleMath::Vector3::One * 0.7f , i + 1);
	}

	// ステージセレクトテキスト
	this->Attach<StageSelectText>(IObject::ObjectID::STAGE_SELECT_TEXT_UI, true,
		{260.0f , 70.0f , 0.0f},
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One * 0.5f);

	// ステージセレクトキーガイド
	this->Attach<StageSelectKeyGuide>(IObject::ObjectID::STAGE_SELECT_KEY_GUIDE, true,
		{ 1280.0f / 2.0f - 30.0f , 676.0f , 0.0f },
		DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3::One * 0.65f);

	// プレイヤー
	this->Attach<Player>(IObject::ObjectID::PLAYER, true,
		{40.0f , 3.0f , 4.0f},
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up,DirectX::XMConvertToRadians(180.0f)),
		DirectX::SimpleMath::Vector3::One * 0.1f,
		nullptr);


	// フェードの作成
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();

	SceneMessenger::GetInstance()->Clear();
	SceneMessenger::GetInstance()->Register(this);

	// ステートコントローラーの作成
	this->CreateStateController();
}

void StageSelectScene::Start()
{
	// BGMを再生
	m_commonResources->GetAudioManager()->PlayFadeInBgm(XACT_WAVEBANK_SOUNDS_GAMEOVERSCENE, 1.0f);

	// ステートマシンスタート処理
	m_currentState->PreUpdate();

	// Tweenを設定
	Player* player = this->SearchObject<Player>(IObject::ObjectID::PLAYER);
	player->GetTransform()->GetTween()->DOMoveX(-40.0f, 20.0f).SetLoops(100, Tween::LoopType::Restart);
	player->GetTransform()->GetTween()->DORotationY(10.0f, 2.0f).SetLoops(100, Tween::LoopType::Increment);
	
	// BGMを再生
	// m_commonResources->GetAudioManager()->PlayFadeInBgm(XACT_WAVEBANK_SOUNDS_GAMEOVERSCENE, 1.0f);

	m_commonResources->GetCollisionManager()->Start();
}

void StageSelectScene::Update()
{
	const float deltaTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// 現在のステートを更新
	m_currentState->Update(deltaTime);

	// オブジェクトの更新処理
	//for (const auto& object : m_objects)
	//{
	//	// object->Update();
	//}

	// Transformのみ更新する
	Player* player = this->SearchObject<Player>(IObject::ObjectID::PLAYER);
	player->GetTransform()->Update();

}

void StageSelectScene::Render()
{
	m_commonResources->GetCollisionManager()->CheckCollision();
	m_commonResources->GetCollisionManager()->Render();
	//モデルの描画
	m_commonResources->GetRenderManager()->Render();

}


void StageSelectScene::Finalize()
{

}

void StageSelectScene::CreateStateController()
{
	// ステートの作成
	m_fadeInState          = std::make_unique<FadeInState>(m_fade.get());
	m_fadeOutState         = std::make_unique<FadeOutState>(m_fade.get(), FadeOutState::ChageSceneID::PLAY_SCENE);
	m_stageSelectMainState = std::make_unique<StageSelectMainState>();
	// 現在のステートを設定
	m_currentState = m_fadeInState.get();
}

/// <summary>
/// カメラを作成する
/// </summary>
void StageSelectScene::CreateCamera()
{
	// カメラの作成
	std::unique_ptr<ICamera> camera = std::make_unique<FixedCamera>(
		DirectX::SimpleMath::Vector3{ 0.0f , 2.0f , -2.0f },
		DirectX::SimpleMath::Quaternion::Identity);
	camera->Initialize();

	// カメラをマネージャーに設定
	m_commonResources->GetCameraManager()->Attach(std::move(camera));
}


void StageSelectScene::ChangeState(IState* newState)
{
	// 事後処理
	m_currentState->PostUpdate();
	// 現在のステートを切り替える
	m_currentState = newState;
	// 事前処理
	m_currentState->PreUpdate();
}

void StageSelectScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::FADE_IN:
			this->ChangeState(m_stageSelectMainState.get());
			break;
		case Message::FADE_OUT:
			this->ChangeState(m_fadeOutState.get());
			break;
		case Message::FADE_OUT_MENU_SCENE:
			// IDを変更
			dynamic_cast<FadeOutState*>(m_fadeOutState.get())->SetSceneID(FadeOutState::ChageSceneID::MENU_SCENE);
			// ステートを変更
			this->ChangeState(m_fadeOutState.get());
			break;
		case Message::MAIN:
			this->ChangeState(m_stageSelectMainState.get());
		default:
			break;
	}
}
