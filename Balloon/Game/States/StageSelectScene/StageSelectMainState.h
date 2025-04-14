// ============================================
// 
// �t�@�C����: StageSelectMainState.h
// �T�v: StageSelectMainState.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IState.h"
#include "Framework/SceneManager.h"
#include "Game/Fade/Fade.h"

class InputManager;


class StageSelectMainState : public IState
{
public:

public:

    // �R���X�g���N�^
    StageSelectMainState();
    // �f�X�g���N�^
    ~StageSelectMainState() override = default;

public:
    // ����������
    void PreUpdate() override;
    // �X�V����
    void Update(const float& deltaTime) override;
    // �I������
    void PostUpdate() override;

private:
   // ���̓}�l�[�W���[
    InputManager* m_inputManager;
   
};