// ============================================
// 
// ファイル名: PlayScene.cpp
// 概要: プレイシーン
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Scenes/Header/PlayScene.h"
#include "Framework/CommonResources.h"

#include "Framework/RenderManager.h"
#include "Framework/Tween/Tween.h"
#include "Framework/CollisionManager.h"
#include "Game/Message/SceneMessenger.h"
#include "Game/Message/ObjectMessenger.h"

#include "Interface/IScene.h"
#include "Interface/IObject.h"

#include "Game/Player/Header/Player.h"
#include "Game/Enemy/Enemy.h"
#include "Game/Cloud/Cloud.h"
#include "Game/Enemy/Enemy.h"
#include "Game/Fade/Fade.h"
#include "Game/Stage/Stage.h"

#include "Game/Cameras/TPSKeyCamera.h"
#include "Game/Cameras/FollowCamera.h"
#include "Game/Cameras/FixedCamera.h"
#include "Game/Cameras/DebugCamera.h"

#include "Game/States/Fade/FadeInState.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/States/ReadyGoState.h"
#include "Game/States/PlayScene/PlayMainState.h"
#include "Framework/Resources/StageResources.h"

// UI
#include "Game/UI/PlayKeyGuideUI.h"
#include "Game/UI/HeightMeterUI.h"
#include "Game/UI/PlayerIconUI.h"
#include "Game/UI/TimeFrameUI.h"
#include "Game/UI/ScoreFrameUI.h"
#include "Game/UI/BalloonGageFrameUI.h"
#include "Game/UI/BalloonGageUI.h"
#include "Game/UI/HPGageFrameUI.h"
#include "Game/UI/HPGageUI.h"
#include "Game/UI/ReadyGoUI.h"
#include "Game/UI/TimerUI.h"
#include "Game/UI/ScoreUI.h"



PlayScene::PlayScene()
	:
	m_enemys{}
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

	// オブジェクトの作成
	this->CreateObject();
	// UIの作成
	this->CreateUI();
	// フェードの作成
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();
	// ステートを作成
	this->CreateState();

	Player* player = this->SearchObject<Player>(IObject::ObjectID::PLAYER);

	// メッセンジャーに登録
	ObjectMessenger::GetInstance()->Register(0, player);
	ObjectMessenger::GetInstance()->Register(1, this->SearchObject<ScoreUI>(IObject::ObjectID::SCORE_UI));
	ObjectMessenger::GetInstance()->Register(2, this->SearchObject<BalloonGageUI>(IObject::ObjectID::BALLOON_GAGE_UI));
	ObjectMessenger::GetInstance()->Register(3, this->SearchObject<HPGageUI>(IObject::ObjectID::HP_GAGE_UI));


	std::unique_ptr<ICamera> camera = std::make_unique<FixedCamera>(DirectX::SimpleMath::Vector3(0.0f, 10.0f, 15.0f),
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(30.0f)) * 
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180.0f)));
	camera->Initialize();
	// カメラを管理者に渡す
	m_commonResources->GetCameraManager()->Attach(std::move(camera));

	camera = std::make_unique<FollowCamera>(player->GetTransform(),
		DirectX::SimpleMath::Vector3(0.0f, 6.0f, -6.0f ));
	camera->Initialize();
	// カメラを管理者に渡す
	m_commonResources->GetCameraManager()->Attach(std::move(camera));
}

void PlayScene::Start()
{
	// シーンを登録する
	SceneMessenger::GetInstance()->Clear();
	SceneMessenger::GetInstance()->Register(this);

	// オブジェクトの更新を行う
	for (const auto& object : m_objects)
	{
		// 更新処理
		object->Update();
		// Transformの更新処理
		object->GetTransform()->Update();
	}

	m_currentState->PreUpdate();
	m_commonResources->GetCollisionManager()->Start();
	// BGMを再生
	m_commonResources->GetAudioManager()->PlayFadeInBgm(XACT_WAVEBANK_SOUNDS_PLAYSCENE, 3.0f);
}

void PlayScene::Update()
{
	float elapsedTime = (float)CommonResources::GetInstance()->GetStepTimer()->GetElapsedSeconds();

	// 現在のステートを更新
	m_currentState->Update(elapsedTime);

	/*m_debugCamera->Update();
	m_commonResources->GetCameraManager()->SetViewMatrix(m_debugCamera->GetViewMatrix());*/
}

void PlayScene::Render()
{
	m_commonResources->GetCollisionManager()->CheckCollision();
	m_commonResources->GetCollisionManager()->Render();
	//モデルの描画
	m_commonResources->GetRenderManager()->Render();
}


void PlayScene::Finalize()
{

}

/// <summary>
/// オブジェクトの作成
/// </summary>
void PlayScene::CreateObject()
{
	using namespace DirectX::SimpleMath;

	this->Attach<Player>(IObject::ObjectID::PLAYER, true,
		Vector3::Zero, Quaternion::Identity, Vector3::One * 0.1f,nullptr
	);
	this->Attach<Enemy>(IObject::ObjectID::ENEMY, true,
		{0.0f , 0.0f , 3.0f}, Quaternion::Identity, Vector3::One * 0.1f, nullptr
	);
	this->Attach<Enemy>(IObject::ObjectID::ENEMY, true,
		{ -3.0f , -4.0f , 3.0f }, Quaternion::Identity, Vector3::One * 0.1f, nullptr
	);

	this->Attach<Stage>(IObject::ObjectID::STAGE, true,
		Vector3::Zero, Quaternion::Identity, Vector3::One, nullptr
	);
	
}

/// <summary>
/// UIを作成
/// </summary>
void PlayScene::CreateUI()
{
	using namespace DirectX::SimpleMath;

	StageResources::StageData stageData = StageResources::GetInstance()->GetStageData(1);

	Player* player = this->SearchObject<Player>(IObject::ObjectID::PLAYER);

	this->Attach<HeightMeterUI>(IObject::ObjectID::HEIGHT_METER_UI, false,
		Vector3(1180.0f, 720.0f / 2.0f, 0.0f), Quaternion::Identity, Vector3::One * 0.6f
	);
	this->Attach<PlayerIconUI>(IObject::ObjectID::PLAYER_ICON_UI, false,
		Vector3(1126.0f, 360.0f, 0.0f), Quaternion::Identity, Vector3::One * 0.07f,player->GetTransform()
	);
	this->Attach<PlayKeyGuideUI>(IObject::ObjectID::PLAY_SCENE_KEYS_GUIDE_UI, false,
		Vector3(1020.0f, 600.0f, 0.0f), Quaternion::Identity, Vector3::One * 0.6f
	);
	this->Attach<TimeFrameUI>(IObject::ObjectID::TIME_FRAME_UI, false,
		Vector3(1180.0f, 720.0f / 7.5f, 0.0f), Quaternion::Identity, Vector3::One * 0.6f
	);
	this->Attach<ScoreFrameUI>(IObject::ObjectID::SCORE_FRAME_UI, false,
		Vector3(1180.0f / 8.0f, 720.0f / 7.5f, 0.0f), Quaternion::Identity, Vector3::One * 0.6f
	);
	this->Attach<BalloonGageFrameUI>(IObject::ObjectID::BALLOON_GAGE_FRAME_UI, false,
		Vector3(1020.0f / 7.0f, 555.0f, 0.0f), Quaternion::Identity, Vector3::One * 0.6f
	);
	this->Attach<BalloonGageUI>(IObject::ObjectID::BALLOON_GAGE_UI, false,
		Vector3(1020.0f / 7.0f, 600.0f, 0.0f), Quaternion::Identity, Vector3::One * 0.6f
	);
	this->Attach<HPGageFrameUI>(IObject::ObjectID::BALLOON_GAGE_FRAME_UI, false,
		Vector3(390.0f, 600.0f, 0.0f), Quaternion::Identity, Vector3::One * 0.6f
	);
	this->Attach<HPGageUI>(IObject::ObjectID::HP_GAGE_UI, false,
		Vector3(390.0f, 600.0f, 0.0f), Quaternion::Identity, {0.6f , 0.55f , 0.0f}
	);
	this->Attach<TimerUI>(IObject::ObjectID::TIMER_UI, false,
		Vector3(1180.0f, 720.0f / 7.5f, 0.0f), Quaternion::Identity, { 0.12f, 0.3f ,0.2f }, false , stageData.time
	);
	this->Attach<ReadyGoUI>(IObject::ObjectID::READY_GO_UI, true,
		Vector3(1280.0f + 600.0f , 720.0f / 2.0f , 0.0f), Quaternion::Identity, Vector3::One * 0.6f
	);
	this->Attach<ScoreUI>(IObject::ObjectID::SCORE_UI, false,
		Vector3(1180.0f / 8.0f, 720.0f / 7.5f, 0.0f), Quaternion::Identity, { 0.2f, 0.4f ,0.2f }
	);
}

/// <summary>
/// ステートを作成
/// </summary>
void PlayScene::CreateState()
{
	std::vector<IObject*> objects;
	for (const auto& object : m_objects)
	{
		objects.push_back(object.get());
	}
	
	// ステートの作成
	m_fadeInState = std::make_unique<FadeInState>(m_fade.get());
	m_fadeOutState = std::make_unique<FadeOutState>(m_fade.get(), FadeOutState::ChageSceneID::MENU_SCENE);
	m_countdown = std::make_unique<ReadyGoState>(this->SearchObject<ReadyGoUI>(IObject::ObjectID::READY_GO_UI));
	m_playMainState = std::make_unique<PlayMainState>(objects);

	// 現在のステートを設定
	m_currentState = m_fadeInState.get();
}

/// <summary>
/// ステートを変更する
/// </summary>
/// <param name="newState"></param>
void PlayScene::ChangeState(IState* newState)
{
	// 事後処理
	m_currentState->PostUpdate();
	// 現在のステートを切り替える
	m_currentState = newState;
	// 事前処理
	m_currentState->PreUpdate();
}

/// <summary>
///	メッセージを受け取る
/// </summary>
/// <param name="messageID"></param>
void PlayScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::FADE_IN:
			this->ChangeState(m_countdown.get());
			break;
		case Message::FADE_OUT:
			break;
		case Message::COUNTDOWN:
			this->ChangeState(m_playMainState.get());
			break;
		case Message::FADE_OUT_GAME_CLEAR_SCENE:
			// IDを変更
			dynamic_cast<FadeOutState*>(m_fadeOutState.get())->SetSceneID(FadeOutState::ChageSceneID::GAME_CLEAR_SCENE);
			// ステートを変更
			this->ChangeState(m_fadeOutState.get());
			break;
		case Message::FADE_OUT_GAME_OVER_SCENE:
			// IDを変更
			dynamic_cast<FadeOutState*>(m_fadeOutState.get())->SetSceneID(FadeOutState::ChageSceneID::GAME_OVER_SCENE);
			// ステートを変更
			this->ChangeState(m_fadeOutState.get());
			break;

		default:
			break;
	}
}