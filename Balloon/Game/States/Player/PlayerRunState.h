// ============================================
// 
// �t�@�C����: PlayerRunState.h
// �T�v: PlayerRunState.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class Transform;
class PhysicsBody;


class PlayerRunState : public IState
{
public:
    // �R���X�g���N�^
    PlayerRunState(Transform* transform , PhysicsBody* physicsBody);
    // �f�X�g���N�^
    ~PlayerRunState() = default;

    // ����������
    void PreUpdate() override;
    // �X�V����
    void Update(const float& deltaTime) override;
    // �I������
    void PostUpdate() override;

private:
    // �ړ�����
    DirectX::SimpleMath::Vector3 GetMovementDirection();

private:

    // �v���C���[Transform
    Transform* m_transform;
    // �v���C���[��������
    PhysicsBody* m_physicsBody;
};