#include "pch.h"
#include "Scenes/TitleScene/TitleScene.h"
#include "Shader/2DSpriteShader/Sprite2DShader.h"
#include "Game/Fade/Fade.h"
#include "Game/Sky/SkySphere.h"

#include "Framework/InputManager.h"
#include "Framework/AudioManager.h"
#include "Framework/TweenManager.h"
#include "Framework/Tween.h"
#include "Interface/IScene.h"
#include "Sounds.h"




TitleScene::TitleScene(SceneManager* scene_manager)
{
	// グラフィックスインスタンスを取得する
	m_graphics = Graphics::GetInstance();
	// シーンマネージャーのインスタンスを取得する
	m_scene_manager = scene_manager;
	// インプットマネージャーのインスタンスを取得する
	m_input_manager = InputManager::GetInstance();
	// オーディオマネージャーのインスタンスを取得する
	m_audioManager = AudioManager::GetInstance();
	// Tweenマネージャーのインスタンスを取得する
	m_tweenManager = TweenManager::GetInstance();
	
}

void TitleScene::Initialize()
{
	// スカイスフィア作成
	m_skySphere = std::make_unique<SkySphere>();
	m_skySphere->Initialize();


	m_titleLogo = std::make_unique<Sprite2DShader>();
	m_spaceKey  = std::make_unique<Sprite2DShader>();
	m_startText = std::make_unique<Sprite2DShader>();

	// タイトルロゴ
	m_titleLogo->Initialize({ 200.0f - 100.0f,95,0.0f },DirectX::SimpleMath::Quaternion::Identity,DirectX::SimpleMath::Vector3::One * 0.5f,
		L"Resources/Shaders/UI_PS.cso");
	// スペースキー
	m_spaceKey->Initialize({ 1280.0f / 4.0f + 30,720.0f / 2.0f + 70,0.0f }, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.4f,
		L"Resources/Shaders/UI_PS.cso");
	// スタートテキスト
	m_startText->Initialize({1280.0f / 4.0f + 60,720.0f / 2.0f + 50,0.0f}, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.4f,
		L"Resources/Shaders/UI_PS.cso");
	

	// テクスチャのロード
	m_titleLogo->LoadTexture(L"Resources\\Textures\\Logo2.png",1);
	m_spaceKey->LoadTexture(L"Resources\\Textures\\SpaceKey.png", 1);
	m_startText->LoadTexture(L"Resources\\Textures\\StartText.png",1);

	// フェードの作成
	m_fade = std::make_unique<Fade>(m_scene_manager);
	 m_fade->FadeIN();
	//m_fade->FadeIN();
	// BGMを再生する
	m_audioManager->PlayFadeOutBgm(XACT_WAVEBANK_SOUNDS_TITLESCENE,2.0f);

	m_position = DirectX::SimpleMath::Vector3::Zero;


	// アニメーションの作成と設定
	// 1. 現在の位置（m_position）を対象にしたTweenを作成
	auto tween = std::make_shared<Tween>(m_position);

	// 2. アニメーションの終了位置と持続時間を設定
	tween->DOMove({ 10, 5, 0 }, 2.0f)             // {10, 5, 0} の位置まで2秒間で移動するよう設定
		.SetDelay(3.0f)                           // アニメーション開始を3秒遅らせる
		.SetLoops(2, Tween::LoopType::Yoyo)       // Yoyo（往復）モードで2回繰り返す
		.SetEase(Tween::EaseType::EaseInOutQuad); // イージングにEaseInOutQuadを使用

	// 3. 作成したTweenをTweenManagerに登録
	// TweenManagerはアニメーションを管理し、必要に応じて更新・削除を行う
	m_tweenManager->RegisterTween(tween);
}

void TitleScene::Start()
{

}


void TitleScene::Update(float elapsed_time)
{
	m_skySphere->Update(elapsed_time);

	// デバッグシーンに移動
	if (m_input_manager->GetKeyboardTracker()->IsKeyReleased(DirectX::Keyboard::F1))
	{
		// 効果音を鳴らす
		m_audioManager->PlaySE();
		// BGMを停止
		m_audioManager->StopFadeInBgm(1.0f);
		
		//m_fade->ChangeSceneFadeOUT<HomeScene>();
		return;
	}
	// スペースでプレイシーンに移動
	if (m_input_manager->GetKeyboardTracker()->IsKeyPressed(DirectX::Keyboard::Space))
	{

		// 効果音を鳴らす
		//m_audioManager->PlaySE();

		/*m_scene_manager->NextSceneLoade<PlayScene>([this]() {
			m_scene_manager->ChageScene();
			});*/

		// BGMを停止
		m_audioManager->StopFadeInBgm(1.0f);
		m_fade->ChangeSceneFadeOUT<PlayScene>();
		return;
	}
}

void TitleScene::Render()
{
	m_skySphere->Render();

	m_spaceKey->Render();
	m_startText->Render();

	m_titleLogo->Render();

	

	m_fade->Render();


	//// 親の情報を表示
	//ImGui::Begin("Hierarchy");

	//float position[3] = { m_position.x,  m_position.y, m_position.z };
	//ImGui::DragFloat3("testTween", position);

	//ImGui::End();

	/*m_graphics->GetSpriteBatch()->Begin();
	m_graphics->DrawString(10.0f, 60.0f, L"TitleScene");
	m_graphics->GetSpriteBatch()->End();*/
}

void TitleScene::Finalize()
{

}