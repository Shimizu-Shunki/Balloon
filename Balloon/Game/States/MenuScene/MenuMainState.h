// ============================================
// 
// �t�@�C����: MenuMainState.h
// �T�v: MenuMainState.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class StateController;
class InputManager;
class IObject;

class MenuMainState : public IState
{
public:
    // �R���X�g���N�^
    MenuMainState(std::vector<IObject*> buttons);
    // �f�X�g���N�^
    ~MenuMainState() = default;

    // ����������
    void PreUpdate() override;
    // �X�V����
    void Update(const float& deltaTime) override;
    // �I������
    void PostUpdate() override;

private:

    void SelectButton();

private:
    std::vector<IObject*> m_buttons;

    InputManager* m_inputManager;

    // ���݂̃{�^��
    int m_buttonIndex;
};