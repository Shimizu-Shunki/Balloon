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
	// 経過時間
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// ステートコントローラーを更新する
	for (const auto& stateController : m_controllers)
	{
		// 現在のステートの更新を行う
		stateController->GetState()->OnStateUpdate(stateController.get(), elapsedTime);
		// トランジションの判定
		stateController->CheckTransitions();
	}
}

void StateMachine::Start()
{
	// 初期ステートのスタート処理
	for (const auto& stateController : m_controllers)
	{
		// 現在のステートの更新を行う
		stateController->GetState()->OnStateEnter(stateController.get());
	}
}