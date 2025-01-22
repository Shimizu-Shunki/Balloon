#pragma once
#include "Framework/StateMachine/StateController.h"
#ifndef ISTATE_DEFINED
#define ISTATE_DEFINED

class StateController;

// IStateインタフェースを定義する(GOF Stateパターン)
class IState
{
public:
	virtual ~IState() = default;

    // 初期化処理
    virtual void OnStateEnter(StateController* stateController) = 0;
    // 更新処理
    virtual void OnStateUpdate(StateController* stateController, const float& deltaTime) = 0;
    // 終了処理
    virtual void OnStateExit(StateController* stateController) = 0;
};

#endif		// ISTATE_DEFINED
