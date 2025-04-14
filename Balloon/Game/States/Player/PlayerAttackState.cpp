// ============================================
// 
// �t�@�C����: PlayerAttackState.cpp
// �T�v: �v���C���[�A�^�b�N�X�e�[�g
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/Player/PlayerAttackState.h"
#include "Game/Message/ObjectMessenger.h"
#include "Framework/StateMachine/StateController.h"
#include "Game/PhysicsBody/PhysicsBody.h"
#include "Game/Player/Header/Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerAttackState::PlayerAttackState(Player* player)
{
	m_player = player;
}

/// <summary>
/// ��������
/// </summary>
/// <param name="stateController">�R���g���[���[</param>
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
/// �X�V����
/// </summary>
/// <param name="stateController">�R���g���[���[</param>
/// <param name="deltaTime">�o�ߎ���</param>
void PlayerAttackState::Update(const float& deltaTime)
{
	// �o�ߎ��Ԃ��X�V
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
/// �I������
/// </summary>
/// <param name="stateController">�R���g���[���[</param>
void PlayerAttackState::PostUpdate()
{

}

