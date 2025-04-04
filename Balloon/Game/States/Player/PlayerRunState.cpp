#include "Framework/pch.h"
#include "Game/States/Player/PlayerRunState.h"
#include "Framework/StateMachine/StateController.h"
#include "Framework/InputManager.h"
#include "Game/Transform/Transform.h"
#include "Game/PhysicsBody/PhysicsBody.h"
#include "Game/Message/ObjectMessenger.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayerRunState::PlayerRunState(Transform* transform, PhysicsBody* physicsBody)
{
	m_transform = transform;
	m_physicsBody = physicsBody;
}

/// <summary>
/// 初期処理
/// </summary>
void PlayerRunState::PreUpdate()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">経過時間</param>
void PlayerRunState::Update(const float& deltaTime)
{
	// キーボードステート
	InputManager* input = InputManager::GetInstance();

	// キーが押されていなければアイドルステートへ
	if (
		!input->OnKey(InputManager::Keys::Left) &&
		!input->OnKey(InputManager::Keys::Right) &&
		!input->OnKey(InputManager::Keys::Up) &&
		!input->OnKey(InputManager::Keys::Down)
		)
	{
		// メッセージを送信する
		ObjectMessenger::GetInstance()->Dispatch(0, Message::ObjectMessageID::PLAYER_IDLE);
	}

	// 入力に基づく方向ベクトルを取得
	DirectX::SimpleMath::Vector3 movementDirection = this->GetMovementDirection();
	// 力を加える
	m_physicsBody->AddForce(movementDirection * 100.0f);
}

/// <summary>
/// 終了処理
/// </summary>
void PlayerRunState::PostUpdate()
{

}

/// <summary>
/// 移動方向を取得する
/// </summary>
/// <returns>移動方向ベクトル</returns>
DirectX::SimpleMath::Vector3 PlayerRunState::GetMovementDirection()
{
	// キーボードステート
	InputManager* input = InputManager::GetInstance();

	// 方向
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::Identity;

	// 上キー
	if (input->OnKey(InputManager::Keys::Up))
	{
		direction += DirectX::SimpleMath::Vector3::Backward;
	}
	// 下キー
	if (input->OnKey(InputManager::Keys::Down))
	{
		direction += DirectX::SimpleMath::Vector3::Forward;
	}
	// 右キー
	if (input->OnKey(InputManager::Keys::Right))
	{
		rotation *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-2.0f));
	}
	// 左キー
	if (input->OnKey(InputManager::Keys::Left))
	{
		rotation *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(2.0f));
	}

	m_transform->SetLocalRotation(m_transform->GetLocalRotation() * rotation);

	// プレイヤーの回転角（クォータニオン）に基づいて方向を回転させる
	direction = DirectX::SimpleMath::Vector3::Transform(direction, m_transform->GetLocalRotation());

	// Y成分をゼロにして水平面に制限
	direction.y = 0.0f;

	// 正規化して移動方向を返す
	direction.Normalize();

	return direction;
}

