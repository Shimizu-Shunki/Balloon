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

    // �R���X�g���N�^
    FadeInState(Fade* fade);
    // �f�X�g���N�^
    ~FadeInState() override;

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
};