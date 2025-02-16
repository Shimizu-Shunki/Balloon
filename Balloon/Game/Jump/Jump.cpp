#include "Framework/pch.h"
#include "Game/Jump/Jump.h"
#include "Framework/CommonResources.h"
#include "Game/UI/JumpFrame.h"
#include "Game/UI/JumpMemory.h"
#include "Game/PhysicsBody/PhysicsBody.h"

Jump::Jump(PhysicsBody* physicBody)
{
    // ���L���\�[�X�̃C���X�^���X���擾����
    m_commonResources = CommonResources::GetInstance();
    // �I�u�W�F�N�g���擾
    /*m_object = object;*/
    m_physicBody = physicBody;
}

void Jump::Initialize()
{
    // �X�v���C�g�쐬
    m_jumpFrame = std::make_unique<JumpFrame>();
    m_jumpFrame->Initialize();
    m_jumpMemory = std::make_unique<JumpMemory>();
    m_jumpMemory->Initialize();

    // �񕜎��ԏ�����
    recoveryRate = 0.5f;
    // �N�[���_�E����ԏ�����
    isCooldown = false;
    currentJumps = 10000;
    cooldownTime = 3.0f;
}

void Jump::Update()
{
    float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();
   
    if (m_commonResources->GetInputManager()->OnKeyDown(InputManager::Keys::Space))
    {
        this->TryJump();
    }

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

float Jump::TryJump()
{
    float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();
    
    if (currentJumps > 0) {
        --currentJumps;

        // �W�����v����
        // �W�����v�������s��
        float vecY = 300.0f * elapsedTime;

        DirectX::SimpleMath::Vector3 jampFoce = { 0.0f , 1000.0f , 0.0f };

        m_physicBody->SetFoce(m_physicBody->GetFoce() + jampFoce);

        // �N�[���_�E�������X�^�[�g
        isCooldown = true;
        elapsedTimeSinceLastJump = 0.0f;

        return vecY;
    }

    return 0.0f;
}