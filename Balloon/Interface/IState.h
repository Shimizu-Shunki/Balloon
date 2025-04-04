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

	// 事前更新する
	virtual void PreUpdate() = 0;
	// 更新する
	virtual void Update(const float& elapsedTime) = 0;
	// 事後更新する
	virtual void PostUpdate() = 0;
};

#endif		// ISTATE_DEFINED
