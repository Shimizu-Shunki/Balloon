// ============================================
// 
// ファイル名: GameClearMainState.h
// 概要: GameClearMainState.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IState.h"
#include "Framework/SceneManager.h"
#include "Game/Fade/Fade.h"

class InputManager;
class SceneMessenger;

class GameClearMainState : public IState
{
public:

public:

    // コンストラクタ
    GameClearMainState();
    // デストラクタ
    ~GameClearMainState() override = default;

public:
    // 初期化処理
    void PreUpdate() override;
    // 更新処理
    void Update(const float& deltaTime) override;
    // 終了処理
    void PostUpdate() override;

private:
   // 入力マネージャー
    InputManager* m_inputManager;
    
};