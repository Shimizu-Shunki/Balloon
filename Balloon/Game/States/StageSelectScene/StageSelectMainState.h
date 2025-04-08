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
    ~StageSelectMainState() override;

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