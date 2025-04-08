#include "Framework/pch.h"
#include "Game/States/StageSelectScene/StageSelectMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Message/SceneMessenger.h"

// コンストラクタ
StageSelectMainState::StageSelectMainState()
{
	// 入力マネージャーのインスタンスを入力
	m_inputManager = InputManager::GetInstance();
}

// デストラクタ
StageSelectMainState::~StageSelectMainState()
{

}

// 初期化処理
void StageSelectMainState::PreUpdate()
{
	
}

// 更新処理
void StageSelectMainState::Update(const float& deltaTime)
{
	// 左右キーでステージを選択
	// 左キー押したとき
	if (m_inputManager->OnKeyDown(InputManager::Keys::Left))
	{

	}
	// 右キー押したとき
	if (m_inputManager->OnKeyDown(InputManager::Keys::Right))
	{

	}

	// ESCキーでメニューシーンへ移動
	if (m_inputManager->OnKeyDown(InputManager::Keys::Escape))
	{
		SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_MENU_SCENE);
	}
}

// 終了処理
void StageSelectMainState::PostUpdate()
{

}