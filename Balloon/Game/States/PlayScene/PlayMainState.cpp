#include "Framework/pch.h"
#include "Game/States/PlayScene/PlayMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"

// �R���X�g���N�^
PlayMainState::PlayMainState()
{
	// ���̓}�l�[�W���[�̃C���X�^���X�����
	m_inputManager = InputManager::GetInstance();
}

// �f�X�g���N�^
PlayMainState::~PlayMainState()
{

}

// ����������
void PlayMainState::OnStateEnter(StateController* stateController)
{
	
}

// �X�V����
void PlayMainState::OnStateUpdate(StateController* stateController, const float& deltaTime)
{
	// �X�y�[�X����͂�����v���C�V�[���ֈȍ~
	if (m_inputManager->OnKeyDown(InputManager::Keys::Space))
	{
		// �p�����[�^�[�̕ύX
		stateController->SetParameter("FadeOUT", true);
	}
}

// �I������
void PlayMainState::OnStateExit(StateController* stateController)
{

}