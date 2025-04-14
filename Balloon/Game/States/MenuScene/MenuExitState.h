// ============================================
// 
// ファイル名: MenuExitState.h
// 概要: MenuExitState.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class StateController;

class MenuExitState : public IState
{
public:
    // コンストラクタ
    MenuExitState();
    // デストラクタ
    ~MenuExitState() = default;

    // 初期化処理
    void PreUpdate() override;
    // 更新処理
    void Update(const float& deltaTime) override;
    // 終了処理
    void PostUpdate() override;
};