// ============================================
// 
// ファイル名: PlayerAttackState.cpp
// 概要: プレイヤーアタックステート
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/Player/PlayerAttackState.h"
#include "Game/Message/ObjectMessenger.h"
#include "Framework/StateMachine/StateController.h"
#include "Game/PhysicsBody/PhysicsBody.h"
#include "Game/Player/Header/Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerAttackState::PlayerAttackState(Player* player)
{
	m_player = player;
}

/// <summary>
/// 初期処理
/// </summary>
/// <param name="stateController">コントローラー</param>
void PlayerAttackState::PreUpdate()
{
	m_elapsedTime = 0.0f;
	m_moveingTime = 0.2f;

	DirectX::SimpleMath::Vector3 velocity = { 0.0f , 0.0f ,6.0f };
	velocity = DirectX::SimpleMath::Vector3::Transform(velocity, m_player->GetTransform()->GetLocalRotation());
	velocity.y = -6.0f;
	m_player->GetPhysicsBody()->SetVelocity(
		velocity * 2.0f
	);
}
/// <summary>
/// 更新処理
/// </summary>
/// <param name="stateController">コントローラー</param>
/// <param name="deltaTime">経過時間</param>
void PlayerAttackState::Update(const float& deltaTime)
{
	// 経過時間を更新
	m_elapsedTime += deltaTime;

	if (m_elapsedTime >= m_moveingTime)
	{
		DirectX::SimpleMath::Vector3 velocity = { 0.0f , 0.0f ,0.0f };
		m_player->GetPhysicsBody()->SetVelocity(
			velocity
		);

		ObjectMessenger::GetInstance()->Dispatch(0, Message::ObjectMessageID::PLAYER_IDLE);
	}
}
/// <summary>
/// 終了処理
/// </summary>
/// <param name="stateController">コントローラー</param>
void PlayerAttackState::PostUpdate()
{

}

