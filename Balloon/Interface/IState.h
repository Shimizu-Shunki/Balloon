// ============================================
// 
// �t�@�C����: IState.h
// �T�v: ��ԑJ�ڂɂ�����X�V�������`����i�C���^�[�t�F�[�X�j
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Framework/StateMachine/StateController.h"

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

