#pragma once
#include "Interface/IState.h"

class StateController;

class PlayerRunAirState : public IState
{
public:
    // �R���X�g���N�^
    PlayerRunAirState();
    // �f�X�g���N�^
    ~PlayerRunAirState() = default;

    // ����������
    void OnStateEnter(StateController* stateController);
    // �X�V����
    void OnStateUpdate(StateController* stateController, const float& deltaTime);
    // �I������
    void OnStateExit(StateController* stateController);
};