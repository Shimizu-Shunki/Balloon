// ============================================
// 
// ファイル名: IState.h
// 概要: 状態遷移における更新処理を定義する（インターフェース）
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Framework/StateMachine/StateController.h"

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

