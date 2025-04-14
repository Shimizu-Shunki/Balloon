// ============================================
// 
// ファイル名: MenuMainState.h
// 概要: MenuMainState.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class StateController;
class InputManager;
class IObject;

class MenuMainState : public IState
{
public:
    // コンストラクタ
    MenuMainState(std::vector<IObject*> buttons);
    // デストラクタ
    ~MenuMainState() = default;

    // 初期化処理
    void PreUpdate() override;
    // 更新処理
    void Update(const float& deltaTime) override;
    // 終了処理
    void PostUpdate() override;

private:

    void SelectButton();

private:
    std::vector<IObject*> m_buttons;

    InputManager* m_inputManager;

    // 現在のボタン
    int m_buttonIndex;
};