#include "Framework/pch.h"
#include "Game/States/Fade/FadeInState.h"
#include "Game/Fade/Fade.h"

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
void FadeInState::OnStateEnter(StateController* stateController)
{
	// �t�F�[�h�C�����s��
	m_fade->FadeIN(1.0f);
}

// �X�V����
void FadeInState::OnStateUpdate(StateController* stateController, const float& deltaTime)
{
	if (!m_fade->GetIsActive())
	{
		// �p�����[�^�[�̕ύX
		stateController->SetParameter("FadeIN", true);
	}
}

// �I������
void FadeInState::OnStateExit(StateController* stateController)
{

}