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
    // �R���X�g���N�^
    FadeOutState(Fade* fade, const FadeOutState::ChageSceneID& chageSceneID);
    // �f�X�g���N�^
    ~FadeOutState() override;

    // �V�[��ID��ύX
    void SetSceneID(const FadeOutState::ChageSceneID& chageSceneID) { m_chageSceneId = chageSceneID; }

public:
    // ����������
    void PreUpdate() override;
    // �X�V����
    void Update(const float& deltaTime) override;
    // �I������
    void PostUpdate() override;

private:

    // �V�[���}�l�[�W���[
    SceneManager* m_sceneManager;
	// �t�F�[�h����
    Fade* m_fade;

    // �V�[��ID
    ChageSceneID m_chageSceneId;
  
};