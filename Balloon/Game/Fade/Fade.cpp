#include "Framework/pch.h"
#include "Game/Fade/Fade.h"
#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"

#include "Framework/CommonResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Fade::Fade()
	:
    m_textureSizeW(1280),
    m_textureSizeH(720),
    m_isActive(false),
    m_duration{},
    m_curentRuleProgress{},
    m_curentTime{},
    m_startProgress{},
    m_endProgress{}
{
    // ���L���\�[�X�̃C���X�^���X���擾����
    m_commonResources = CommonResources::GetInstance();

    m_sceneManager = CommonResources::GetInstance()->GetSceneManager();
}

/// <summary>
/// ����������
/// </summary>
void Fade::Initialize()
{
    int width, height;

    // Transform�̍쐬
    m_transform = std::make_unique<Transform>();
    // Image�̍쐬
    m_image = std::make_unique<Image>();
    // Material�̍쐬
    m_material = std::make_unique<DefaultUi>();

    // Image�̏�����
    m_image->Initialize(true, m_material.get(), m_transform.get());
    m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetTitleLogo(), width, height);
    m_image->SetRuleTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetRuleTexture());
    m_image->SetIsActive(true);

    m_commonResources->GetRenderManager()->AddSprite(m_image.get());

    // Transform�̏�����
    m_transform->SetLocalPosition({ 1280.0f / 2.0f , 720.0f / 2.0f , 0.0f });
    m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
    m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
    m_transform->SetRect({ 0.0f,0.0f,(float)width,(float)height });
    m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

    // �}�e���A��������������
    this->InitialMaterial(width, height);
}

/// <summary>
/// �X�V����
/// </summary>
void Fade::Update()
{
    // �t���[��
    float elapseTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

    // �t�F�[�h���Ŗ�����΃X�L�b�v
    if (!m_isActive) return;

    auto material = dynamic_cast<DefaultUi*>(m_material.get());

    // �o�ߎ��Ԃ��X�V
    m_curentTime += elapseTime;

    // ���`��Ԃ��g�p���ĉ��ʂ��X�V
    float t = m_curentTime / m_duration; // 0.0f�`1.0f �͈̔�
    t = std::min(t, 1.0f); // t��1�𒴂��Ȃ��悤�ɐ���

    // ���݂̐i�s�x���X�V
    m_curentRuleProgress = m_startProgress + t * (m_endProgress - m_startProgress);
    // ���݂̐i�s�x���X�V����
    material->SetRuleProgress(m_curentRuleProgress);

    // �t�F�[�h���I��������
    if (m_curentTime >= 1.0f) {
        m_curentRuleProgress = m_endProgress;
        // �ŏI���ʂ�ݒ�
        material->SetRuleProgress(m_curentRuleProgress);

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

    // �萔�o�b�t�@�̍X�V
    material->UpdateConstBuffer();
}

/// <summary>
/// �t�F�[�h�C�����s��
/// </summary>
/// <param name="duration">�b��</param>
void Fade::FadeIN(float duration)
{
    // �t�F�[�h�������Ȃ� true ��Ԃ�
    if (m_isActive) return;

    // �t�F�[�h���Ԃ�ݒ�
    m_duration = duration;

    auto material = dynamic_cast<DefaultUi*>(m_material.get());

    // ���[���摜�̐i�s�x��������
    material->SetRuleInverse(0.0f);
    // ���[���摜�̔��]�ݒ�
    material->SetRuleProgress(0.0f);

    // �X�^�[�g�i�s�x
    m_startProgress = 1.0f;
    // �G���h�i�s�x
    m_endProgress = 0.0f;

    // �t�F�[�h�������A�N�e�B�u�ɂ���
    m_isActive = true;

    // �萔�o�b�t�@�̍X�V
    material->UpdateConstBuffer();
}


/// <summary>
/// �}�e���A���̏�����
/// </summary>
/// <param name="width">�e�N�X�`���T�C�Y��</param>
/// <param name="height">�e�N�X�`���T�C�Y����</param>
void Fade::InitialMaterial(int width, int height)
{
    auto material = dynamic_cast<DefaultUi*>(m_material.get());

    material->SetPixelShader(CommonResources::GetInstance()->GetResources()->GetShaderResources()->GetUI_PS());
    material->SetWindowSize({ 1280.0f,720.0f });
    material->SetTextureSize({ (float)width, (float)height });
    material->SetUseTexture(0.0f);
    material->SetUseRuleTexture(1.0f);
    material->SetRuleProgress(0.0f);
    material->SetRuleInverse(0.0f);
}
