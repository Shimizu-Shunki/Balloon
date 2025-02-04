#pragma once
#include "Interface/IState.h"
#include "Framework/SceneManager.h"
#include "Game/Fade/Fade.h"


class Fade;
class SceneManager;

class FadeInState : public IState
{
public:
   
public:

    // コンストラクタ
    FadeInState(Fade* fade);
    // デストラクタ
    ~FadeInState() override;

public:
    // 初期化処理
    void OnStateEnter(StateController* stateController) override;
    // 更新処理
    void OnStateUpdate(StateController* stateController, const float& deltaTime) override;
    // 終了処理
    void OnStateExit(StateController* stateController) override;

private:

    // シーンマネージャー
    SceneManager* m_sceneManager;
    // フェード処理
    Fade* m_fade;
};