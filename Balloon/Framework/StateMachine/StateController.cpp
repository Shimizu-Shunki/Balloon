#include "Framework/pch.h"
#include "Framework/StateMachine/StateMachine.h"
#include "Framework/StateMachine/StateController.h"
#include "Framework/StateMachine/Parameters.h"
#include "Framework/StateMachine/Transition.h"
#include "Interface/IState.h"


// コンストラクタ
StateController::StateController(bool mapMode)
	:
	m_useMap(mapMode)
{
}

// マップモード
void StateController::AddTransition(std::string stateName, std::string toStateName, std::string parameterName, Parameters::ParameterValue condition)
{
	// state
	auto state = m_states.find(stateName);
	// toState
	auto toState = m_states.find(toStateName);

	if (state != m_states.end() && toState != m_states.end())
	{
		// トランジションを追加する
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
	// キーが存在するかチェック
	if (it == m_transitions.end()) return;

	for (auto& transition : it->second)
	{
		// トランジションの判定処理
		for (auto& [key, value] : m_parameters)
		{
			// トランジションの条件
			const auto& conditions = transition->GetCondition();

			// キーが存在するかチェック
			auto it = conditions.find(key);
			if (it != conditions.end() && value == it->second)
			{
				// 条件が満たすときステートを切り替える
				this->ChageState(transition->GetNextState());
			}
		}
	}
}


void StateController::ChageState(IState* nextState)
{
	// 現在のステートの終了処理を行う
	m_currentState->OnStateExit(this);
	// 次のステートセットする
	m_currentState = nullptr;
	m_currentState = nextState;
	// 初期処理を行う
	m_currentState->OnStateEnter(this);
}

// デフォルトのステートを設定
void StateController::SetDeffultState(std::string stateName)
{
	// state
	auto state = m_states.find(stateName);

	if (state != m_states.end())
	{
		m_currentState = state->second.get();
	}
}
