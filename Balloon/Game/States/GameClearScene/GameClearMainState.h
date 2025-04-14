// ============================================
// 
// �t�@�C����: GameClearMainState.h
// �T�v: GameClearMainState.cpp�̃w�b�_�[�t�@�C��
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

class GameClearMainState : public IState
{
public:

public:

    // �R���X�g���N�^
    GameClearMainState();
    // �f�X�g���N�^
    ~GameClearMainState() override = default;

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