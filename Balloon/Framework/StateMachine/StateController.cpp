#include "Framework/pch.h"
#include "Framework/StateMachine/StateMachine.h"
#include "Framework/StateMachine/StateController.h"
#include "Framework/StateMachine/Parameters.h"
#include "Framework/StateMachine/Transition.h"
#include "Interface/IState.h"


// �R���X�g���N�^
StateController::StateController(bool mapMode)
	:
	m_useMap(mapMode)
{
}

// �}�b�v���[�h
void StateController::AddTransition(std::string stateName, std::string toStateName, std::string parameterName, Parameters::ParameterValue condition)
{
	// state
	auto state = m_states.find(stateName);
	// toState
	auto toState = m_states.find(toStateName);

	if (state != m_states.end() && toState != m_states.end())
	{
		// �g�����W�V������ǉ�����
		m_transitions[state->second.get()].push_back(std::make_unique<Transition>(toState->second.get(), parameterName, condition));
	}
}

void StateController::SetParameter(std::string parameterName, Parameters::ParameterValue condition)
{
	if (m_parameters.find(parameterName) != m_parameters.end()) {
		m_parameters[parameterName] = condition;
	}
}

void StateController::CheckTransitions()
{
	auto it = m_transitions.find(m_currentState);
	// �L�[�����݂��邩�`�F�b�N
	if (it == m_transitions.end()) return;

	for (auto& transition : it->second)
	{
		// �g�����W�V�����̔��菈��
		for (auto& [key, value] : m_parameters)
		{
			// �g�����W�V�����̏���
			const auto& conditions = transition->GetCondition();

			// �L�[�����݂��邩�`�F�b�N
			auto it = conditions.find(key);
			if (it != conditions.end() && value == it->second)
			{
				// �������������Ƃ��X�e�[�g��؂�ւ���
				this->ChageState(transition->GetNextState());
			}
		}
	}
}


void StateController::ChageState(IState* nextState)
{
	// ���݂̃X�e�[�g�̏I���������s��
	m_currentState->OnStateExit(this);
	// ���̃X�e�[�g�Z�b�g����
	m_currentState = nullptr;
	m_currentState = nextState;
	// �����������s��
	m_currentState->OnStateEnter(this);
}

// �f�t�H���g�̃X�e�[�g��ݒ�
void StateController::SetDeffultState(std::string stateName)
{
	// state
	auto state = m_states.find(stateName);

	if (state != m_states.end())
	{
		m_currentState = state->second.get();
	}
}
