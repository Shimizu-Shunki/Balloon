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
    // ���L���\�[�X�̃C���X�^���X���擾����
    m_commonResources = CommonResources::GetInstance();
    // �R���e�L�X�g���擾����
    m_context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// �t�F�[�h�p�̃X�v���C�g���쐬
	m_spriteMaterial = std::make_unique<SpriteMaterial>(
        m_commonResources->GetDeviceResources()->GetD3DDevice(),
        m_commonResources->GetDeviceResources()->GetD3DDeviceContext());

    // �V�F�[�_�[�����[�h����
    // ���_�V�F�[�_�[
    m_spriteMaterial->LoadVertexShader(L"Resources\\Shaders\\cso\\UI_VS.cso");
    // �W�I���g���V�F�[�_�[
    m_spriteMaterial->LoadGeometryShader(L"Resources\\Shaders\\cso\\UI_GS.cso");
    // �s�N�Z���V�F�[�_�[
    m_spriteMaterial->LoadPixelShader(L"Resources\\Shaders\\cso\\UI_PS.cso");

    // �e�N�X�`�������[�h����
    m_spriteMaterial->LoadTexture(m_commonResources->GetResources()->GetTitleLogo(), m_textureSizeW, m_textureSizeH);
    // ���[���摜�����[�h
    m_spriteMaterial->LoadRuleTexture(m_commonResources->GetResources()->GetTitleLogo());

    // �o�b�t�@�̏�����
    m_constBuffer.windowSize = { (float)m_textureSizeW,(float)m_textureSizeH };
    // �^�����̃e�N�X�`���Ƃ��ė��p���邽�ߖ���������
    m_constBuffer.useTexture = 0;
    // ���[���摜���g�p����
    m_constBuffer.useRuleTexture = 1;
    // ���[�����]���Ȃ�
    m_constBuffer.ruleInverse = 0;
    // ���[���摜�̐i�s�x������
    m_constBuffer.ruleProgress = 0;
}

// �f�X�g���N�^
Fade::~Fade()
{

}

// �X�V����
void Fade::Update()
{
    // �t���[��
    float elapseTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

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


void Fade::Render()
{
    if (!m_isActive) return;
    // �`�揀��
    m_spriteMaterial->Begin();
    // �`��
    m_context->Draw(1, 0);
    // �`��I������
    m_spriteMaterial->End();
}