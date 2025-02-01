#include "Framework/pch.h"
#include "Framework/StateMachine/Transition.h"
#include "Framework/StateMachine/Parameters.h"
#include "Interface/IState.h"


Transition::Transition(IState* nextState, std::string parameterName, Parameters::ParameterValue condition, int priority)
	:
	m_nextState(nextState),
	m_priority(priority)
{
	// �������i�[
	m_condition[parameterName] = condition;
}

