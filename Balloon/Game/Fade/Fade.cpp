#include "pch.h"
#include "Game/Fade/Fade.h"
#include "Shader/2DSpriteShader/Sprite2DShader.h"
#include "Scenes/SceneManager/SceneManager.h"



// �R���X�g���N�^
Fade::Fade()
	:
	m_sprite{},
	m_fadeTime{},
    m_isActive(false)
{
    m_sceneManager = SceneManager::GetInstance();
	// �t�F�[�h�p�̃X�v���C�g���쐬
	m_sprite = std::make_unique<Sprite2DShader>();
	// ����������
	m_sprite->Initialize(DirectX::SimpleMath::Vector3::Zero, 
        DirectX::SimpleMath::Quaternion::Identity,
        DirectX::SimpleMath::Vector3::One, L"Resources/Shaders/UI_PS.cso");
	
    // �摜�����[�h
    m_sprite->LoadTexture(L"Resources\\Textures\\rule1080p\\022.png", 0);
    // ���[���摜�����[�h
    m_sprite->LoadRuleTexture(L"Resources\\Textures\\rule1080p\\022.png");

    m_sprite->SetRuleActive(true);
    m_sprite->SetTexActive(false);
	// �^�C��
	m_fadeTime = 0;
}


// �f�X�g���N�^
Fade::~Fade()
{

}

//// �t�F�[�h�C������
//bool Fade::FadeIN()
//{
//    // �t�F�[�h�������Ȃ� true ��Ԃ�
//    if (m_isActive)
//        return true;
//
//    m_isActive = true; // �t�F�[�h�����J�n
//    m_sprite->SetTime(1.0f); // �A���t�@�l���V�F�[�_�[�ɐݒ�
//
//    m_sprite->SetReversed(0);
//
//    // �񓯊��^�X�N���N��
//    m_future = std::async(std::launch::async, [this]() 
//    {
//        // �����A���t�@�l�i���S�s�����j
//        float alpha = 1.0f;   
//        // �A���t�@�l�̌����ʁi60FPS��ōX�V�j
//        const float step = 0.016f; 
//
//        while (alpha > 0.0f)
//        {
//            alpha -= step;
//            if (alpha < 0.0f) alpha = 0.0f;
//            // �A���t�@�l���V�F�[�_�[�ɐݒ�
//            m_sprite->SetRuleProgress(alpha); 
//            
//            // �t���[���ҋ@ (16ms �� 60FPS����)
//            std::this_thread::sleep_for(std::chrono::milliseconds(16));
//        }
//        // ������ɃA�N�e�B�u��Ԃ�����
//        m_isActive = false; 
//    });
//    // �t�F�[�h�������� true ��Ԃ�
//    return m_isActive; 
//}
//
//
//// �t�F�[�h�A�E�g����
//bool Fade::FadeOUT()
//{
//    return false;
//}

void Fade::Render()
{
    if (!m_isActive) return;

    m_sprite->Render();       // �`�揈��
}