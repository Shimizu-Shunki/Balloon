#include "pch.h"
#include "Scenes/PlayScene/PlayScene.h"
#include "Game/Camera/TPSCamera.h"

#include "Framework/InputManager.h"
#include "Game/Fade/Fade.h"
#include "Game/UI/Timer.h"
#include "Game/UI/Countdown.h"
#include "Game/Sky/SkySphere.h"
#include "Game/Player/Player.h"
#include "Framework/AudioManager.h"

#include "Game/Camera/DebugCamera.h"
#include "Game/Object/Object.h"
#include "Framework/CollisionManager.h"
#include "Shader/Material/SeaMaterial.h"

#include "Interface/IScene.h"




PlayScene::PlayScene(SceneManager* scene_manager)
{
	// グラフィックスインスタンスを取得する
	m_graphics = Graphics::GetInstance();
	// シーンマネージャーのインスタンスを取得する
	m_scene_manager = scene_manager;
	// オーディオマネージャーのインスタンスを取得する
	m_audioManager = AudioManager::GetInstance();
	// インプットマネージャーのインスタンスを取得する
	m_input_manager = InputManager::GetInstance();
}

void PlayScene::Initialize()
{
	// 当たり判定管理を作成
	m_collisionManager = std::make_unique<CollisionManager>();

	// TPSカメラ作成　初期化
	m_tpsCamera = std::make_unique<TPSCamera>();
	m_tpsCamera->Initialize();

	// スカイスフィア作成
	m_skySphere = std::make_unique<SkySphere>();
	m_skySphere->Initialize();

	m_SeaMaterial = std::make_unique<SeaMaterial>();
	m_SeaMaterial->Initialize();

	
	// プレイヤーの作成
	m_player = std::make_unique<Player>(m_collisionManager.get(), nullptr, 3, DirectX::SimpleMath::Vector3::Up * 26.0f , 0.0f);
	m_player->Initialize(IComponent::ObjectID::PLAYER, true);

	// 床オブジェクトを作成と初期化
	this->InitializeObject();

	m_collisionManager->Attach(m_player.get());
	// 敵の作成

	// UIの初期化
	// フェードの作成
	m_fade = std::make_unique<Fade>(m_scene_manager);
	
	// タイマー作成
	m_timer = std::make_unique<Timer>();
	m_timer->Initialize(false,66.0f);
	// カウントダウン作成
	m_countdown = std::make_unique<Countdown>();
	m_countdown->Initialize();

	// 当たり判定の初期化
	m_collisionManager->Initialize();

	// BGMを再生する
	m_audioManager->PlayFadeOutBgm(XACT_WAVEBANK_SOUNDS_PLAYSCENE, 2.0f);

	m_isFade = true;
}

void PlayScene::Start()
{
	// フェード処理を行う
	m_fade->FadeIN();
}


void PlayScene::Update(float elapsed_time)
{
	// スカイスフィア（青空）更新処理
	m_skySphere->Update(elapsed_time);
	// 足場の更新処理
	UpdateFloor(elapsed_time);


	// プレイヤー更新処理
	m_player->Update(elapsed_time, DirectX::SimpleMath::Vector3::Zero, m_tpsCamera->GetRotation());
	// カメラの更新処理
	m_tpsCamera->Update(elapsed_time, m_player->GetPosition());
	// ビュー行列の作成
	m_tpsCamera->CalculateViewMatrix();

	
	// 敵の更新処理

	// タイマーの処理
	m_timer->Update(elapsed_time);
	// カウントダウンの処理
	m_countdown->Update(elapsed_time);

	// 当たり判定を行う
	m_collisionManager->CheckCollision();
}

void PlayScene::Render()
{
	// スカイスフィア（青空）更新処理
	m_skySphere->Render();

	// 床の描画
	m_floorPlayerStart->Render();
	m_floorLeftUp->Render();
	m_floorRightUp->Render();
	m_floorLeftDown->Render();
	m_floorRightDown->Render();
	m_floorPlayerStart->Render();

	// プレイヤーの描画
	m_player->Render();
	// 敵の描画

	

	// 床の描画
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	m_graphics->DrawGridFloor({ 10.0f,0.0f,0.0f }, { 0.0f,0.0f,10.0f }, 20);
	m_graphics->DrawPrimitiveEnd();

	m_SeaMaterial->Render();

	// UIの描画
	
	// タイマーの描画
	m_timer->Render();
	// カウントダウンの描画
	m_countdown->Render();
	// フェード
	m_fade->Render();

	/*m_graphics->GetSpriteBatch()->Begin();
	m_graphics->DrawString(10.0f, 60.0f, L"PlayScene");
	m_graphics->GetSpriteBatch()->End();*/
}

void PlayScene::Finalize()
{

}

void PlayScene::InitializeObject()
{
	// オブジェクトの初期化
	m_floorPlayerStart = std::make_unique<Object>();
	m_floorLeftUp      = std::make_unique<Object>();
	m_floorRightUp     = std::make_unique<Object>();
	m_floorLeftDown    = std::make_unique<Object>();
	m_floorRightDown   = std::make_unique<Object>();

	m_floorPlayerStart->Initialize(IComponent::ObjectID::CLOUD , true);
	m_floorLeftUp->Initialize(IComponent::ObjectID::CLOUD, true);
	m_floorRightUp->Initialize(IComponent::ObjectID::CLOUD, true);
	m_floorLeftDown->Initialize(IComponent::ObjectID::CLOUD, true);
	m_floorRightDown->Initialize(IComponent::ObjectID::CLOUD, true);

	m_collisionManager->Attach(m_floorPlayerStart.get());
	m_collisionManager->Attach(m_floorLeftUp.get());
	m_collisionManager->Attach(m_floorRightUp.get());
	m_collisionManager->Attach(m_floorLeftDown.get());
	m_collisionManager->Attach(m_floorRightDown.get());

}

void PlayScene::UpdateFloor(float elapsed_time)
{
	// 床オブジェクト更新処理
	m_floorPlayerStart->Update(elapsed_time, {  0.0f , 24.0f ,   0.0f }, DirectX::SimpleMath::Quaternion::Identity);
	m_floorLeftUp->Update(elapsed_time,      {-15.0f , 18.0f ,  15.0f }, DirectX::SimpleMath::Quaternion::Identity);
	m_floorRightUp->Update(elapsed_time,     { 15.0f , 18.0f ,  15.0f }, DirectX::SimpleMath::Quaternion::Identity);
	m_floorLeftDown->Update(elapsed_time,    {-15.0f , 18.0f , -15.0f }, DirectX::SimpleMath::Quaternion::Identity);
	m_floorRightDown->Update(elapsed_time,   { 15.0f , 18.0f , -15.0f }, DirectX::SimpleMath::Quaternion::Identity);
}