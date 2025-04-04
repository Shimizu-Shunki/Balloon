#pragma once
#include "Interface/IState.h"
#include "Framework/SceneManager.h"
#include "Game/Fade/Fade.h"

class InputManager;
class SceneMessenger;

class TitleMainState : public IState
{
public:

public:

    // �R���X�g���N�^
    TitleMainState();
    // �f�X�g���N�^
    ~TitleMainState() override;

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
    // �V�[�����b�Z���W���[
    SceneMessenger* m_sceneMessenger;
};