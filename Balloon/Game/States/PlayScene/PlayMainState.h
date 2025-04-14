// ============================================
// 
// �t�@�C����: PlayMainState.h
// �T�v: PlayMainState.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IState.h"
#include "Framework/SceneManager.h"
#include "Game/Fade/Fade.h"


class InputManager;
class Enemy;
class Player;
class IObject;

class PlayMainState : public IState
{
public:

public:

    // �R���X�g���N�^
    PlayMainState(std::vector<IObject*> objects);
    // �f�X�g���N�^
    ~PlayMainState() override = default;

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

   // �I�u�W�F�N�g
   std::vector<IObject*> m_objects;
};