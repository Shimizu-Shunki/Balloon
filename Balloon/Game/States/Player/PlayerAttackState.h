// ============================================
// 
// �t�@�C����: PlayerAttackState.h
// �T�v: PlayerAttackState.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class Transform;
class PhysicsBody;
class Player;

class PlayerAttackState : public IState
{
public:
    // �R���X�g���N�^
    PlayerAttackState(Player* player);
    // �f�X�g���N�^
    ~PlayerAttackState() = default;

    // ����������
    void PreUpdate() override;
    // �X�V����
    void Update(const float& deltaTime) override;
    // �I������
    void PostUpdate() override;

private:

    // �v���C���[�I�u�W�F�N�g
    Player* m_player;

    // �A�^�b�N����
    float m_moveingTime;
    // �o�ߎ���
    float m_elapsedTime;
};