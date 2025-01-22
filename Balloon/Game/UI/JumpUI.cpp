#include "pch.h"
#include "Game/Player/Jump.h"
#include "Shader/2DSpriteShader/Sprite2DShader.h"

Jump::Jump()
{

}


void Jump::Initialize()
{
    // �}�e���A���̍쐬
    m_jumpMaterial = std::make_unique<Sprite2DShader>();
    m_hpBarMaterial = std::make_unique<Sprite2DShader>();

    // �}�e���A��������
    m_jumpMaterial->Initialize({ 20.0f , 60.0f ,0.0f }, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.5f ,
        L"Resources/Shaders/UI_PS.cso");
    // �}�e���A��������
    m_hpBarMaterial->Initialize({ 72.0f , 78.0f ,0.0f }, DirectX::SimpleMath::Quaternion::Identity, DirectX::SimpleMath::Vector3::One * 0.45f + DirectX::SimpleMath::Vector3::Up * 0.2f,
        L"Resources/Shaders/UI_PS.cso");


    // �e�N�X�`�������[�h����
    m_jumpMaterial->LoadTexture(L"Resources\\Textures\\JumpFrameUI.png", 1);
    m_hpBarMaterial->LoadTexture(L"Resources\\Textures\\JumpBar.png", 1);

    m_hpBarMaterial->SetReversed(0);
    m_hpBarMaterial->SetRuleActive(true);
    m_hpBarMaterial->SetRuleProgress(1.0f);
    m_hpBarMaterial->SetTexActive(1);


    // �񕜎��ԏ�����
    recoveryRate = 0.5f;
    // �N�[���_�E����ԏ�����
    isCooldown = false;
    currentJumps = 10;
    cooldownTime = 3.0f;
}


void Jump::Update(const float& elapsedTime)
{

    m_hpBarMaterial->SetRect(
        { 0.0f,0.0f, 
        100.0f * currentJumps ,50.0f }
    );
    m_hpBarMaterial->SetRenderSize( 100.0f * currentJumps , 50.0f);

    // �N�[���^�C��������
    if (isCooldown) {
        elapsedTimeSinceLastJump += elapsedTime;

        // �N�[���_�E�����I�������ꍇ
        if (elapsedTimeSinceLastJump >= cooldownTime) {
            // �N�[���_�E���I��
            isCooldown = false;
            // �񕜎��Ԃ����Z�b�g
            elapsedTimeSinceLastJump = 0.0f; 
        }
        return;
    }

    // �N�[���_�E�����I�����ĉ񕜏����Ɉڍs
    if (currentJumps < MAX_JUMPS) {
        elapsedTimeSinceLastJump += elapsedTime;
        // �񕜎��Ԃɉ����ĉ񕜂��s��
        if (elapsedTimeSinceLastJump >= recoveryRate) {
            ++currentJumps;
            // �񕜎��Ԃ����Z�b�g
            elapsedTimeSinceLastJump = 0.0f; 
        }
    }
}

void Jump::Render()
{
    // UI��`�悳����
    m_jumpMaterial->Render();

   m_hpBarMaterial->Render();
}

float Jump::TryJump(const float& elapsedTime)
{
    if (currentJumps > 0) {
        --currentJumps;
       
        // �W�����v����
        // �W�����v�������s��
        float vecY = 300.0f * elapsedTime;

        // �N�[���_�E�������X�^�[�g
        isCooldown = true;
        elapsedTimeSinceLastJump = 0.0f;

        return vecY;
    }

    return 0.0f;
}


void Jump::DebugRender()
{
    ImGui::Begin("Jump");
    ImGui::DragInt("JumpIndex", &currentJumps);
    ImGui::End();
}