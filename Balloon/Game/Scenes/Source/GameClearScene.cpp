#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/Header/GameClearScene.h"
#include "Interface/IScene.h"
#include "Interface/IObject.h"
#include "Framework/StateMachine/StateMachine.h"
#include "Game/States/Fade/FadeInState.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/States/TitleScene/TitleMainState.h"


GameClearScene::GameClearScene()
{
	m_commonResources = CommonResources::GetInstance();
}


GameClearScene::~GameClearScene()
{

}

void GameClearScene::Initialize()
{
	
	


	// フェードの作成
	m_fade = std::make_unique<Fade>();
	m_fade->Initialize();


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
	stateController->AddState<FadeOutState>("FadeOutState", m_fade.get(), FadeOutState::ChageSceneID::TITLE_SCENE);

	// デフォルトのステートを設定
	stateController->SetDeffultState("FadeInState");

	// トランジションの追加
	stateController->AddTransition("FadeInState", "TitleMainState", "FadeIN", true);
	stateController->AddTransition("TitleMainState", "FadeOutState", "FadeOUT", true);

	// ステートコントローラーを追加
	m_stateMachine->AddController(std::move(stateController));


}

void GameClearScene::Start()
{
	// BGMを再生する
	m_stateMachine->Start();
}

void GameClearScene::Update()
{
	m_stateMachine->Update();
	m_fade->Update();
	

}

void GameClearScene::Render()
{
	//モデルの描画
	m_commonResources->GetRenderManager()->Render();
}


void GameClearScene::Finalize()
{

}

