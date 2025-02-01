#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Framework/RenderManager.h"
#include "Game/Scenes/Header/TitleScene.h"
#include "Interface/IScene.h"
#include "Interface/IObject.h"

#include "Game/Player/Header/Player.h"
#include "Framework/StateMachine/StateMachine.h"
#include "Framework/StateMachine/StateController.h"

#include "Game/Cameras/DebugCamera.h"

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
	m_commonResources->GetAudioManager()->PlayFadeInBgm(XACT_WAVEBANK_SOUNDS_TITLESCENE, 1.0f);
}

void TitleScene::Update()
{

}

void TitleScene::Render()
{
	
}


void TitleScene::Finalize()
{

}

