#pragma once
#include "Interface/IState.h"

class StateController;

class PlayerJumpState : public IState
{
public:
    // �R���X�g���N�^
    PlayerJumpState();
    // �f�X�g���N�^
    ~PlayerJumpState() = default;

    // ����������
    void OnStateEnter(StateController* stateController);
    // �X�V����
    void OnStateUpdate(StateController* stateController, const float& deltaTime);
    // �I������
    void OnStateExit(StateController* stateController);
};