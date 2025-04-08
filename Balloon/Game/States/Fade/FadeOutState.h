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
        MENU_SCENE,
        SELECT_SCENE,
        PLAY_SCENE,
        GAME_CLEAR_SCENE,
        GAME_OVER_SCENE,
        EXIT_GAME,
    };

public:
    // コンストラクタ
    FadeOutState(Fade* fade, const FadeOutState::ChageSceneID& chageSceneID);
    // デストラクタ
    ~FadeOutState() override;

    // シーンIDを変更
    void SetSceneID(const FadeOutState::ChageSceneID& chageSceneID) { m_chageSceneId = chageSceneID; }

public:
    // 初期化処理
    void PreUpdate() override;
    // 更新処理
    void Update(const float& deltaTime) override;
    // 終了処理
    void PostUpdate() override;

private:

    // シーンマネージャー
    SceneManager* m_sceneManager;
	// フェード処理
    Fade* m_fade;

    // シーンID
    ChageSceneID m_chageSceneId;
  
};