#pragma once
#include "Interface/IState.h"

class StateController;

class PlayerIdleState : public IState
{
public:
    // �R���X�g���N�^
    PlayerIdleState();
    // �f�X�g���N�^
    ~PlayerIdleState() = default;

    // ����������
    void OnStateEnter(StateController* stateController);
    // �X�V����
    void OnStateUpdate(StateController* stateController, const float& deltaTime);
    // �I������
    void OnStateExit(StateController* stateController);
};