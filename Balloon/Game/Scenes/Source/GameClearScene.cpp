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

	// ステートの作成
	m_fadeInState = std::make_unique<FadeInState>(m_fade.get());
	m_fadeOutState = std::make_unique<FadeOutState>(m_fade.get(), FadeOutState::ChageSceneID::TITLE_SCENE);
	m_gameClearMainState = std::make_unique<TitleMainState>();
	// 現在のステートを設定
	m_currentState = m_fadeInState.get();
}

void GameClearScene::Start()
{
	// BGMを再生する
	m_currentState->PreUpdate();
}

void GameClearScene::Update()
{
	const float deltaTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	m_currentState->Update(deltaTime);

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

void GameClearScene::ChangeState(IState* newState)
{
	// 事後処理
	m_currentState->PostUpdate();
	// 現在のステートを切り替える
	m_currentState = newState;
	// 事前処理
	m_currentState->PreUpdate();
}

void GameClearScene::OnSceneMessegeAccepted(Message::SceneMessageID messageID)
{
	switch (messageID)
	{
		case Message::FADE_IN:
			break;
		case Message::FADE_OUT:
			break;
		default:
			break;
	}
}

