#pragma once
#include "Interface/IState.h"
#include "Framework/SceneManager.h"
#include "Game/Fade/Fade.h"


class InputManager;

class TitleMainState : public IState
{
public:

public:

    // �R���X�g���N�^
    TitleMainState();
    // �f�X�g���N�^
    ~TitleMainState() override;

public:
    // ����������
    void OnStateEnter(StateController* stateController) override;
    // �X�V����
    void OnStateUpdate(StateController* stateController, const float& deltaTime) override;
    // �I������
    void OnStateExit(StateController* stateController) override;

private:
   // ���̓}�l�[�W���[
    InputManager* m_inputManager;
};