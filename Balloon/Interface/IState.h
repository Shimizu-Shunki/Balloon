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

	// ���O�X�V����
	virtual void PreUpdate() = 0;
	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;
	// ����X�V����
	virtual void PostUpdate() = 0;
};

#endif		// ISTATE_DEFINED
