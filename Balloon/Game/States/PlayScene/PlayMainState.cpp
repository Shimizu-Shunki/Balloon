// ============================================
// 
// ファイル名: PlayMainState.cpp
// 概要: プレイシーンのメイン処理ステート
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/PlayScene/PlayMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Player/Header/Player.h"
#include "Game/Enemy/Enemy.h"
#include "Game/Message/SceneMessenger.h"
#include "Game/UI/TimerUI.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayMainState::PlayMainState(std::vector<IObject*> objects)
{
	// 入力マネージャーのインスタンスを入力
	m_inputManager = InputManager::GetInstance();
	// オブジェクトを取得する
	m_objects = objects;
}

/// <summary>
/// 初期処理
/// </summary>
void PlayMainState::PreUpdate()
{
	// オブジェクトを有効化にする
	for (const auto& object : m_objects)
	{
		object->SetIsActive(true);
	}
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void PlayMainState::Update(const float& deltaTime)
{
	(void)deltaTime;

	// オブジェクトの更新を行う
	for (const auto& object : m_objects)
	{
		// 更新処理
		object->Update();
		// Transformの更新処理
		object->GetTransform()->Update();

		if (object->GetObjectID() == IObject::ObjectID::TIMER_UI)
		{
			TimerUI* timerUI = dynamic_cast<TimerUI*>(object);
			if (timerUI->GetTime() <= 0.0f)
			{
				SceneMessenger::GetInstance()->Dispatch(Message::FADE_OUT_GAME_OVER_SCENE);
			}
		}
	}

	// プレイヤーが落ちたら
	if (m_objects[0]->GetTransform()->GetLocalPosition().y <= -10.0f)
	{
		SceneMessenger::GetInstance()->Dispatch(Message::FADE_OUT_GAME_OVER_SCENE);
	}

	// 敵がすべて落ちたら
	if (m_objects[1]->GetTransform()->GetLocalPosition().y <= -10.0f &&
		m_objects[2]->GetTransform()->GetLocalPosition().y <= -10.0f)
	{
		SceneMessenger::GetInstance()->Dispatch(Message::FADE_OUT_GAME_CLEAR_SCENE);
	}	
}

/// <summary>
/// 終了処理
/// </summary>
void PlayMainState::PostUpdate()
{

}