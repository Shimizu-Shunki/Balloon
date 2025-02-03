#include "Framework/pch.h"
#include "Framework/StateMachine/StateMachine.h"
#include "Framework/StateMachine/StateController.h"
#include "Framework/StateMachine/Parameters.h"
#include "Framework/StateMachine/Transition.h"
#include <vector>
#include "Interface/IState.h"
#include "Framework/CommonResources.h"

StateMachine::StateMachine()
{
	m_commonResources = CommonResources::GetInstance();
}

void StateMachine::Update()
{
	// �o�ߎ���
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// �X�e�[�g�R���g���[���[���X�V����
	for (const auto& stateController : m_controllers)
	{
		// ���݂̃X�e�[�g�̍X�V���s��
		stateController->GetState()->OnStateUpdate(stateController.get(), elapsedTime);
		// �g�����W�V�����̔���
		stateController->CheckTransitions();
	}
}

void StateMachine::Start()
{
	// �����X�e�[�g�̃X�^�[�g����
	for (const auto& stateController : m_controllers)
	{
		// ���݂̃X�e�[�g�̍X�V���s��
		stateController->GetState()->OnStateEnter(stateController.get());
	}
}