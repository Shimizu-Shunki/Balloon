// ============================================
// 
// �t�@�C����: FadeInState.cpp
// �T�v: �t�F�[�h�C���̃X�e�[�g
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/Fade/FadeInState.h"
#include "Game/Fade/Fade.h"
#include "Game/Message/SceneMessenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="fade">�t�F�[�h����</param>
FadeInState::FadeInState(Fade* fade)
{
	// �V�[���}�l�[�W���[�̃C���X�^���X���擾����
	m_sceneManager = SceneManager::GetInstance();
	
	m_fade = fade;
}

/// <summary>
/// ����������
/// </summary>
void FadeInState::PreUpdate()
{
	// �t�F�[�h�C�����s��
	m_fade->FadeIN(1.0f);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void FadeInState::Update(const float& deltaTime)
{
	(void)deltaTime;

	// �t�F�[�h�̍X�V���s��
	m_fade->Update();

	if (!m_fade->GetIsActive())
	{
		SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_IN);
	}
}

/// <summary>
/// �I������
/// </summary>
void FadeInState::PostUpdate()
{

}