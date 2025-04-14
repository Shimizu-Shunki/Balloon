// ============================================
// 
// �t�@�C����: MenuSettingState.h
// �T�v: MenuSettingState.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class StateController;

class MenuSettingState : public IState
{
public:
    // �R���X�g���N�^
    MenuSettingState();
    // �f�X�g���N�^
    ~MenuSettingState() = default;

    // ����������
    void PreUpdate() override;
    // �X�V����
    void Update(const float& deltaTime) override;
    // �I������
    void PostUpdate() override;
};