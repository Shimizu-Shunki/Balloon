#pragma once
#include "Framework/StateMachine/StateController.h"
#ifndef ISTATE_DEFINED
#define ISTATE_DEFINED

class StateController;

// IState�C���^�t�F�[�X���`����(GOF State�p�^�[��)
class IState
{
public:
	virtual ~IState() = default;

    // ����������
    virtual void OnStateEnter(StateController* stateController) = 0;
    // �X�V����
    virtual void OnStateUpdate(StateController* stateController, const float& deltaTime) = 0;
    // �I������
    virtual void OnStateExit(StateController* stateController) = 0;
};

#endif		// ISTATE_DEFINED
