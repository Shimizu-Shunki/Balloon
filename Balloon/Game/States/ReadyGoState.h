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

public:

    // �R���X�g���N�^
    ReadyGoState(ReadyGoUI* readyGoUI);
    // �f�X�g���N�^
    ~ReadyGoState() override;

public:
    // ����������
    void OnStateEnter(StateController* stateController) override;
    // �X�V����
    void OnStateUpdate(StateController* stateController, const float& deltaTime) override;
    // �I������
    void OnStateExit(StateController* stateController) override;

private:

    void ReadyGoSetAnimation();


private:

    // �V�[���}�l�[�W���[
    SceneManager* m_sceneManager;
    // ReadyGo��UI
    ReadyGoUI* m_readyGoUI;

    // �؂�ւ��t���O
    bool m_changeFlag;

};