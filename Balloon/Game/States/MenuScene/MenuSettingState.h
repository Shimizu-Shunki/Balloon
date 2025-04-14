// ============================================
// 
// ファイル名: MenuSettingState.h
// 概要: MenuSettingState.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class StateController;

class MenuSettingState : public IState
{
public:
    // コンストラクタ
    MenuSettingState();
    // デストラクタ
    ~MenuSettingState() = default;

    // 初期化処理
    void PreUpdate() override;
    // 更新処理
    void Update(const float& deltaTime) override;
    // 終了処理
    void PostUpdate() override;
};