#pragma once
#include "Interface/IState.h"
#include "Game/Fade/Fade.h"

class Fade;
class SceneManager;

class FadeOutState : public IState
{
public:
    enum class ChageSceneID
    {
        TITLE_SCENE,
        SELECT_SCENE,
        PLAY_SCENE,
        GAME_CLEAR_SCENE,
        GAME_OVER_SCENE,
    };

public:
    // コンストラクタ
    FadeOutState(Fade* fade, const FadeOutState::ChageSceneID& chageSceneID);
    // デストラクタ
    ~FadeOutState() override;

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

    // シーンID
    ChageSceneID m_chageSceneId;
  
};