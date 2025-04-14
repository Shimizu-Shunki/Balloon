// ============================================
// 
// �t�@�C����: PlayerIdleState.cpp
// �T�v: �v���C���[�A�C�h���X�e�[�g
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/Player/PlayerIdleState.h"
#include "Framework/StateMachine/StateController.h"
#include "Framework/InputManager.h"
#include "Game/Message/ObjectMessenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerIdleState::PlayerIdleState()
{

}

/// <summary>
/// ��������
/// </summary>
/// <param name="stateController">�R���g���[���[</param>
void PlayerIdleState::PreUpdate()
{

}
/// <summary>
/// �X�V����
/// </summary>
/// <param name="stateController">�R���g���[���[</param>
/// <param name="deltaTime">�o�ߎ���</param>
void PlayerIdleState::Update(const float& deltaTime)
{
	(void)deltaTime;

	InputManager* input = InputManager::GetInstance();

	// �����L�[�������ꂽ��ړ��X�e�[�g�̃��b�Z�[�W�𑗐M
	if (
		input->OnKeyDown(InputManager::Keys::Left) ||
		input->OnKeyDown(InputManager::Keys::Right) ||
		input->OnKeyDown(InputManager::Keys::Up) ||
		input->OnKeyDown(InputManager::Keys::Down)
		)
	{
		// ���b�Z�[�W�𑗐M����
		ObjectMessenger::GetInstance()->Dispatch(0, Message::ObjectMessageID::PLAYER_RUN);
	}

	// Z�L�[�������ꂽ��A�^�b�N�X�e�[�g�̃��b�Z�[�W�𑗐M����
	if (input->OnKeyDown(InputManager::Keys::Z))
	{
		// �A�^�b�N����
		ObjectMessenger::GetInstance()->Dispatch(3, Message::ObjectMessageID::PLAYER_ATTACK);
	}

}
/// <summary>
/// �I������
/// </summary>
/// <param name="stateController">�R���g���[���[</param>
void PlayerIdleState::PostUpdate()
{

}

