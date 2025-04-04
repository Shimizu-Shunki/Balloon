#pragma once
#include "Interface/IState.h"
#include "Framework/SceneManager.h"
#include "Game/Fade/Fade.h"


class Fade;
class SceneManager;

class FadeInState : public IState
{
public:
   
public:

    // �R���X�g���N�^
    FadeInState(Fade* fade);
    // �f�X�g���N�^
    ~FadeInState() override;

public:
    // ����������
    void PreUpdate() override;
    // �X�V����
    void Update(const float& deltaTime) override;
    // �I������
    void PostUpdate() override;

private:

    // �V�[���}�l�[�W���[
    SceneManager* m_sceneManager;
    // �t�F�[�h����
    Fade* m_fade;
};