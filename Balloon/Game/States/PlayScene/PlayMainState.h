// ============================================
// 
// ファイル名: PlayMainState.h
// 概要: PlayMainState.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IState.h"
#include "Framework/SceneManager.h"
#include "Game/Fade/Fade.h"


class InputManager;
class Enemy;
class Player;
class IObject;

class PlayMainState : public IState
{
public:

public:

    // コンストラクタ
    PlayMainState(std::vector<IObject*> objects);
    // デストラクタ
    ~PlayMainState() override = default;

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

   // オブジェクト
   std::vector<IObject*> m_objects;
};