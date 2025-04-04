#include "Framework/pch.h"
#include "Game/States/Player/PlayerRunState.h"
#include "Framework/StateMachine/StateController.h"
#include "Framework/InputManager.h"
#include "Game/Transform/Transform.h"
#include "Game/PhysicsBody/PhysicsBody.h"
#include "Game/Message/ObjectMessenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerRunState::PlayerRunState(Transform* transform, PhysicsBody* physicsBody)
{
	m_transform = transform;
	m_physicsBody = physicsBody;
}

/// <summary>
/// ��������
/// </summary>
void PlayerRunState::PreUpdate()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void PlayerRunState::Update(const float& deltaTime)
{
	// �L�[�{�[�h�X�e�[�g
	InputManager* input = InputManager::GetInstance();

	// �L�[��������Ă��Ȃ���΃A�C�h���X�e�[�g��
	if (
		!input->OnKey(InputManager::Keys::Left) &&
		!input->OnKey(InputManager::Keys::Right) &&
		!input->OnKey(InputManager::Keys::Up) &&
		!input->OnKey(InputManager::Keys::Down)
		)
	{
		// ���b�Z�[�W�𑗐M����
		ObjectMessenger::GetInstance()->Dispatch(0, Message::ObjectMessageID::PLAYER_IDLE);
	}

	// ���͂Ɋ�Â������x�N�g�����擾
	DirectX::SimpleMath::Vector3 movementDirection = this->GetMovementDirection();
	// �͂�������
	m_physicsBody->AddForce(movementDirection * 100.0f);
}

/// <summary>
/// �I������
/// </summary>
void PlayerRunState::PostUpdate()
{

}

/// <summary>
/// �ړ��������擾����
/// </summary>
/// <returns>�ړ������x�N�g��</returns>
DirectX::SimpleMath::Vector3 PlayerRunState::GetMovementDirection()
{
	// �L�[�{�[�h�X�e�[�g
	InputManager* input = InputManager::GetInstance();

	// ����
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::Identity;

	// ��L�[
	if (input->OnKey(InputManager::Keys::Up))
	{
		direction += DirectX::SimpleMath::Vector3::Backward;
	}
	// ���L�[
	if (input->OnKey(InputManager::Keys::Down))
	{
		direction += DirectX::SimpleMath::Vector3::Forward;
	}
	// �E�L�[
	if (input->OnKey(InputManager::Keys::Right))
	{
		rotation *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-2.0f));
	}
	// ���L�[
	if (input->OnKey(InputManager::Keys::Left))
	{
		rotation *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(2.0f));
	}

	m_transform->SetLocalRotation(m_transform->GetLocalRotation() * rotation);

	// �v���C���[�̉�]�p�i�N�H�[�^�j�I���j�Ɋ�Â��ĕ�������]������
	direction = DirectX::SimpleMath::Vector3::Transform(direction, m_transform->GetLocalRotation());

	// Y�������[���ɂ��Đ����ʂɐ���
	direction.y = 0.0f;

	// ���K�����Ĉړ�������Ԃ�
	direction.Normalize();

	return direction;
}

