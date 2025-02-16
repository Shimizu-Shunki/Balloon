#include "Framework/pch.h"
#include "Framework/StateMachine/StateMachine.h"
#include "Framework/StateMachine/StateController.h"
#include "Framework/StateMachine/Transition.h"
#include "Interface/IState.h"


/// <summary>
/// コンストラクタ
/// </summary>
StateController::StateController()
	:
	m_states{},
	m_parameters{},
	m_transitions{},
	m_currentState{}
{
}

/// <summary>
/// 指定された2つのステート間にトランジションを追加する
/// </summary>
/// <param name="stateName">元のステートの名前</param>
/// <param name="toStateName">遷移先のステートの名前</param>
/// <param name="parameterName">トランジションの条件となるパラメータの名前</param>
/// <param name="condition">トランジションの条件</param>
void StateController::AddTransition(std::string stateName, std::string toStateName, std::string parameterName, ParameterValue condition)
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

/// <summary>
/// 指定されたパラメータに値を設定する
/// </summary>
/// <param name="parameterName">設定するパラメータの名前</param>
/// <param name="condition">パラメータに設定する値</param>
void StateController::SetParameter(std::string parameterName, ParameterValue condition)
{
	if (m_parameters.find(parameterName) != m_parameters.end()) {
		m_parameters[parameterName] = condition;
	}
}

/// <summary>
/// トランジションの更新
/// </summary>
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

/// <summary>
/// ステートを切り替える
/// </summary>
/// <param name="nextState">次のステート</param>
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

/// <summary>
/// デフォルトのステートを設定
/// </summary>
/// <param name="stateName">ステートの名前</param>
void StateController::SetDeffultState(std::string stateName)
{
	// state
	auto state = m_states.find(stateName);

	if (state != m_states.end())
	{
		m_currentState = state->second.get();
	}
}
