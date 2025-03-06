#pragma once
#include "Interface/IState.h"

class StateController;

class PlayerIdleState : public IState
{
public:
    // コンストラクタ
    PlayerIdleState();
    // デストラクタ
    ~PlayerIdleState() = default;

    // 初期化処理
    void OnStateEnter(StateController* stateController);
    // 更新処理
    void OnStateUpdate(StateController* stateController, const float& deltaTime);
    // 終了処理
    void OnStateExit(StateController* stateController);
};