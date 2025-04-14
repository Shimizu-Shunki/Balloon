// ============================================
// 
// �t�@�C����: GameOverMainState.h
// �T�v: GameOverMainState.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IState.h"
#include "Framework/SceneManager.h"
#include "Game/Fade/Fade.h"

class InputManager;
class SceneMessenger;

class GameOverMainState : public IState
{
public:

public:

    // �R���X�g���N�^
    GameOverMainState();
    // �f�X�g���N�^
    ~GameOverMainState() override = default;

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