// ============================================
// 
// �t�@�C����: PlayerIdleState.h
// �T�v: PlayerIdleState.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class Transform;

class PlayerIdleState : public IState
{
public:
    // �R���X�g���N�^
    PlayerIdleState();
    // �f�X�g���N�^
    ~PlayerIdleState() = default;

    // ����������
    void PreUpdate() override;
    // �X�V����
    void Update(const float& deltaTime) override;
    // �I������
    void PostUpdate() override;

private:

    // �v���C���[Transform
    Transform* m_transform;
};