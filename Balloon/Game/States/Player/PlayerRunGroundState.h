#pragma once
#include "Interface/IState.h"

class StateController;

class PlayerRunGroundState : public IState
{
public:
    // �R���X�g���N�^
    PlayerRunGroundState();
    // �f�X�g���N�^
    ~PlayerRunGroundState() = default;

    // ����������
    void OnStateEnter(StateController* stateController);
    // �X�V����
    void OnStateUpdate(StateController* stateController, const float& deltaTime);
    // �I������
    void OnStateExit(StateController* stateController);
};