#include "Framework/pch.h"
#include "Game/States/Fade/FadeInState.h"
#include "Game/Fade/Fade.h"
#include "Game/Message/SceneMessenger.h"

// �R���X�g���N�^
FadeInState::FadeInState(Fade* fade)
{
	// �V�[���}�l�[�W���[�̃C���X�^���X���擾����
	m_sceneManager = SceneManager::GetInstance();
	
	m_fade = fade;
}

// �f�X�g���N�^
FadeInState::~FadeInState()
{

}

// ����������
void FadeInState::PreUpdate()
{
	// �t�F�[�h�C�����s��
	m_fade->FadeIN(1.0f);
}

// �X�V����
void FadeInState::Update(const float& deltaTime)
{
	// �t�F�[�h�̍X�V���s��
	m_fade->Update();

	if (!m_fade->GetIsActive())
	{
		SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_IN);
	}
}

// �I������
void FadeInState::PostUpdate()
{

}