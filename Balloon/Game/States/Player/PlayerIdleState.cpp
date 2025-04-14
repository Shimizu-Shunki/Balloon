// ============================================
// 
// ファイル名: PlayerIdleState.cpp
// 概要: プレイヤーアイドルステート
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/Player/PlayerIdleState.h"
#include "Framework/StateMachine/StateController.h"
#include "Framework/InputManager.h"
#include "Game/Message/ObjectMessenger.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerIdleState::PlayerIdleState()
{

}

/// <summary>
/// 初期処理
/// </summary>
/// <param name="stateController">コントローラー</param>
void PlayerIdleState::PreUpdate()
{

}
/// <summary>
/// 更新処理
/// </summary>
/// <param name="stateController">コントローラー</param>
/// <param name="deltaTime">経過時間</param>
void PlayerIdleState::Update(const float& deltaTime)
{
	(void)deltaTime;

	InputManager* input = InputManager::GetInstance();

	// 方向キーが押されたら移動ステートのメッセージを送信
	if (
		input->OnKeyDown(InputManager::Keys::Left) ||
		input->OnKeyDown(InputManager::Keys::Right) ||
		input->OnKeyDown(InputManager::Keys::Up) ||
		input->OnKeyDown(InputManager::Keys::Down)
		)
	{
		// メッセージを送信する
		ObjectMessenger::GetInstance()->Dispatch(0, Message::ObjectMessageID::PLAYER_RUN);
	}

	// Zキーが押されたらアタックステートのメッセージを送信する
	if (input->OnKeyDown(InputManager::Keys::Z))
	{
		// アタック処理
		ObjectMessenger::GetInstance()->Dispatch(3, Message::ObjectMessageID::PLAYER_ATTACK);
	}

}
/// <summary>
/// 終了処理
/// </summary>
/// <param name="stateController">コントローラー</param>
void PlayerIdleState::PostUpdate()
{

}

