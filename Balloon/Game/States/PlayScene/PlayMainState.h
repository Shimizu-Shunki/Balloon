#pragma once
#include "Interface/IState.h"
#include "Framework/SceneManager.h"
#include "Game/Fade/Fade.h"


class InputManager;
class Enemy;
class Player;

class PlayMainState : public IState
{
public:

public:

    // コンストラクタ
    PlayMainState(Player* player, std::vector<Enemy*> enemys);
    // デストラクタ
    ~PlayMainState() override;

public:
    // 初期化処理
    void OnStateEnter(StateController* stateController) override;
    // 更新処理
    void OnStateUpdate(StateController* stateController, const float& deltaTime) override;
    // 終了処理
    void OnStateExit(StateController* stateController) override;

private:
   // 入力マネージャー
    InputManager* m_inputManager;

    // エネミー
    std::vector<Enemy*> m_enemys;
    // プレイヤー
    Player* m_player;
};