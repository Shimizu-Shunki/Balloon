// ============================================
// 
// �t�@�C����: MenuExitState.h
// �T�v: MenuExitState.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class StateController;

class MenuExitState : public IState
{
public:
    // �R���X�g���N�^
    MenuExitState();
    // �f�X�g���N�^
    ~MenuExitState() = default;

    // ����������
    void PreUpdate() override;
    // �X�V����
    void Update(const float& deltaTime) override;
    // �I������
    void PostUpdate() override;
};