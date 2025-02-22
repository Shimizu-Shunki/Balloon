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
    // �R���X�g���N�^
    FadeOutState(Fade* fade, const FadeOutState::ChageSceneID& chageSceneID);
    // �f�X�g���N�^
    ~FadeOutState() override;

public:
    // ����������
    void OnStateEnter(StateController* stateController) override;
    // �X�V����
    void OnStateUpdate(StateController* stateController, const float& deltaTime) override;
    // �I������
    void OnStateExit(StateController* stateController) override;

private:

    // �V�[���}�l�[�W���[
    SceneManager* m_sceneManager;
	// �t�F�[�h����
    Fade* m_fade;

    // �V�[��ID
    ChageSceneID m_chageSceneId;
  
};