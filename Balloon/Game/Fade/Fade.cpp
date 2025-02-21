#include "Framework/pch.h"
#include "Game/Fade/Fade.h"
#include "Framework/SceneManager.h"
#include "Framework/CommonResources.h"



// �R���X�g���N�^
Fade::Fade()
	:
    m_textureSizeW(1280),
    m_textureSizeH(720),
    m_isActive(false),
    m_duration{},
    m_curentRuleProgress{},
    m_curentTime{},
    m_startProgress{},
    m_endProgress{},
    m_future{}
{
    m_commonResources = CommonResources::GetInstance();
}

void Fade::Initialize()
{
    
    auto commonResources = CommonResources::GetInstance();

    commonResources->GetRenderManager()->AddSprite(this);

    m_sceneManager = commonResources->GetSceneManager();

    // Transform�̍쐬
    m_transform = std::make_unique<Transform>();

    // �}�e���A���̍쐬
    m_spriteMaterial = std::make_unique<SpriteMaterial>(
        commonResources->GetDeviceResources()->GetD3DDevice(), commonResources->GetDeviceResources()->GetD3DDeviceContext());

    // �萔�o�b�t�@��ݒ�
    m_spriteMaterial->SetConstBuffer<ConstBuffer>();

    // �V�F�[�_�[��ݒ�
    m_spriteMaterial->SetVertexShader  (commonResources->GetResources()->GetUI_VS());
    m_spriteMaterial->SetGeometryShader(commonResources->GetResources()->GetUI_GS());
    m_spriteMaterial->SetPixelShader   (commonResources->GetResources()->GetUI_PS());

    int width, height;

    // �摜�����[�h
    m_spriteMaterial->SetTexture(commonResources->GetResources()->GetTitleLogo(), width, height);

    m_spriteMaterial->SetRuleTexture(commonResources->GetResources()->GetRuleTexture());

    m_constBuffer.windowSize = { 1280.0f,720.0f };
    m_constBuffer.textureSize = { (float)width,(float)height };
    m_constBuffer.useTexture = 0;
    m_constBuffer.useRuleTexture = 1;
    m_constBuffer.ruleProgress = 0.0f;
    m_constBuffer.ruleInverse = 0;

    m_transform->SetLocalPosition({ 1280.0f / 2.0f, 720.0f / 2.0f,0.0f });

    m_vertexBuffer.position = DirectX::SimpleMath::Vector4(
        m_transform->GetLocalPosition().x,
        m_transform->GetLocalPosition().y,
        m_transform->GetLocalPosition().z,
        1.0f
    );
    m_vertexBuffer.scale = DirectX::SimpleMath::Vector3::One;

    m_vertexBuffer.color = DirectX::SimpleMath::Vector4::One;

    m_vertexBuffer.rect = { 0.0f , 0.0f , (float)width,(float)height };

    m_vertexBuffer.rotate = DirectX::SimpleMath::Vector3::Zero;

    // �萔�o�b�t�@�̍X�V������
    //m_spriteMaterial->UpdateConstBuffer<ConstBuffer>(m_constBuffer, 0);

    m_spriteMaterial->SetVertexBuffer(m_vertexBuffer);

    m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);    
}



// �X�V����
void Fade::Update()
{
    // �t���[��
    float elapseTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

    if (!m_isActive) return;

    // �o�ߎ��Ԃ��X�V
    m_curentTime += elapseTime;

    // ���`��Ԃ��g�p���ĉ��ʂ��X�V
    float t = m_curentTime / m_duration; // 0.0f�`1.0f �͈̔�
    t = std::min(t, 1.0f); // t��1�𒴂��Ȃ��悤�ɐ���

    // ���݂̐i�s�x���X�V
    m_curentRuleProgress = m_startProgress + t * (m_endProgress - m_startProgress);
    // ���݂̐i�s�x���X�V����
    m_constBuffer.ruleProgress = m_curentRuleProgress;

    // �t�F�[�h���I��������
    if (m_curentTime >= 1.0f) {
        m_curentRuleProgress = m_endProgress;
        // �ŏI���ʂ�ݒ�
        m_constBuffer.ruleProgress = m_curentRuleProgress;

        // �t�F�[�h�A�E�g�̎�
        if (m_endProgress == 1.0f)
        {
            // ���̃V�[���ɑJ�ڂ���
            m_sceneManager->ChageScene();
        }
        // �p�����[�^�[�̏�����
        m_startProgress = 0.0f;
        m_endProgress = 0.0f;
        m_curentRuleProgress = 0.0f;
        m_curentTime = 0.0f;
        
        // �t�F�[�h���A�N�e�B�u
        m_isActive = false;
    }

    m_spriteMaterial->UpdateConstBuffer<ConstBuffer>(m_constBuffer, 0);
}

// �t�F�[�h�C������
void Fade::FadeIN(float duration)
{
    // �t�F�[�h�������Ȃ� true ��Ԃ�
    if (m_isActive) return;

    // �t�F�[�h���Ԃ�ݒ�
    m_duration = duration;

    // ���[���摜�̐i�s�x��������
    m_constBuffer.ruleProgress = 1.0f;
    // ���[���摜�̔��]�����Ȃ�
    m_constBuffer.ruleInverse = 0;

    // �X�^�[�g�i�s�x
    m_startProgress = 1.0f;
    // �G���h�i�s�x
    m_endProgress = 0.0f;

    // �t�F�[�h�������A�N�e�B�u�ɂ���
    m_isActive = true;
}
