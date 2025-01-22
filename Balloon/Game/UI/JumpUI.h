#pragma once
#include "Shader/2DSpriteShader/Sprite2DShader.h"

class Sprite2DShader;

class Jump
{
private:
    // �ő�W�����v��
    const int MAX_JUMPS = 10;


public:
    // �R���X�g���N�^
    Jump();
    // �f�X�g���N�^
    ~Jump() = default;


public:
    // ����������
    void Initialize();
    // �X�V����
    void Update(const float& elapsedTime);
    // �`�揈��
    void Render();
    // �W�����v����
    float TryJump(const float& elapsedTime);

    void DebugRender();

private: 

    // 2D�}�e���A�� HPUI
    std::unique_ptr<Sprite2DShader> m_jumpMaterial;
    // 2D�}�e���A�� HPBarUI
    std::unique_ptr<Sprite2DShader> m_hpBarMaterial;

    // ���݂̃W�����v��
    int currentJumps;
    // �N�[���_�E�����ԁi�b�j
    float cooldownTime;
    // 1�񕜂��Ƃ̎��ԁi�b�j
    float recoveryRate;   
    // �Ō�̃W�����v����̌o�ߎ���
    float elapsedTimeSinceLastJump;
    // �N�[���_�E�������ǂ���
    bool isCooldown;               

};