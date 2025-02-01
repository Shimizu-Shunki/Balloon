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
void StateController::AddTransition(IState* state, IState* toState, std::string parameterName, Parameters::ParameterValue condition)
{
	// トランジションを追加する
	m_transitions[state].push_back(std::make_unique<Transition>(toState, parameterName, condition));
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

