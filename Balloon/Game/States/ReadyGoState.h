// ============================================
// 
// ファイル名: ReadyGoState.h
// 概要: ReadyGoState.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IState.h"
#include "Framework/SceneManager.h"
#include "Game/Fade/Fade.h"


class Fade;
class SceneManager;
class ReadyGoUI;

class ReadyGoState : public IState
{
public:

    // コンストラクタ
    ReadyGoState(ReadyGoUI* readyGoUI);
    // デストラクタ
    ~ReadyGoState() override = default;

public:
    // 初期化処理
    void PreUpdate() override;
    // 更新処理
    void Update(const float& deltaTime) override;
    // 終了処理
    void PostUpdate() override;

private:

    void ReadyGoSetAnimation();


private:

    // シーンマネージャー
    SceneManager* m_sceneManager;
    // ReadyGoのUI
    ReadyGoUI* m_readyGoUI;

    // 切り替えフラグ
    bool m_changeFlag;

};