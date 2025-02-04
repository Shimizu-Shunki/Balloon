#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Framework/RenderManager.h"
#include "Game/Scenes/Header/PlayScene.h"
#include "Interface/IScene.h"
#include "Interface/IObject.h"
#include "Framework/Tween/Tween.h"

#include "Game/Player/Header/Player.h"

#include "Game/Cameras/DebugCamera.h"

#include "Game/Fade/Fade.h"

#include "Framework/CollisionManager.h"

// ステート
#include "Framework/StateMachine/StateController.h"
#include "Framework/StateMachine/StateMachine.h"
#include "Game/States/Fade/FadeInState.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/States/PlayScene/PlayMainState.h"


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


	// フェードの作成
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();

	this->CreateStateStateController();

}

void PlayScene::Start()
{
	m_stateMachine->Start();
	// BGMを再生
	m_commonResources->GetAudioManager()->PlayFadeInBgm(XACT_WAVEBANK_SOUNDS_PLAYSCENE, 3.0f);

	m_commonResources->GetCollisionManager()->Start();
}

void PlayScene::Update()
{
	m_stateMachine->Update();

	m_rootObject[0]->Update();

	m_rootTransform->Update();

	m_debugCamera->Update();
	m_commonResources->GetCameraManager()->SetViewMatrix(m_debugCamera->GetViewMatrix());

	m_fade->Update();
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

void PlayScene::CreateStateStateController()
{
	// ステートマシーンの作成
	m_stateMachine = std::make_unique<StateMachine>();

	// ステートコントローラーの作成
	auto stateController = std::make_unique<StateController>(true);

	// パラメーターの追加
	stateController->AddParameters("FadeIN", false);
	stateController->AddParameters("FadeOUT", false);

	// ステートの追加
	stateController->AddState<FadeInState>("FadeInState", m_fade.get());
	stateController->AddState<PlayMainState>("PlayMainState");
	stateController->AddState<FadeOutState>("FadeOutState", m_fade.get(), FadeOutState::ChageSceneID::TITLE_SCENE);

	// デフォルトのステートを設定
	stateController->SetDeffultState("FadeInState");

	// トランジションの追加
	stateController->AddTransition("FadeInState", "PlayMainState", "FadeIN", true);
	stateController->AddTransition("PlayMainState", "FadeOutState", "FadeOUT", true);

	// ステートコントローラーを追加
	m_stateMachine->AddController(std::move(stateController));
}
