// ============================================
// 
// �t�@�C����: ReadyGoState.h
// �T�v: ReadyGoState.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IState.h"
#include "Framework/SceneManager.h"
#include "Game/Fade/Fade.h"


class Fade;
class SceneManager;
class ReadyGoUI;

class ReadyGoState : public IState
{
public:

    // �R���X�g���N�^
    ReadyGoState(ReadyGoUI* readyGoUI);
    // �f�X�g���N�^
    ~ReadyGoState() override = default;

public:
    // ����������
    void PreUpdate() override;
    // �X�V����
    void Update(const float& deltaTime) override;
    // �I������
    void PostUpdate() override;

private:

    void ReadyGoSetAnimation();


private:

    // �V�[���}�l�[�W���[
    SceneManager* m_sceneManager;
    // ReadyGo��UI
    ReadyGoUI* m_readyGoUI;

    // �؂�ւ��t���O
    bool m_changeFlag;

};