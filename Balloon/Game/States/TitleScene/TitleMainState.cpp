#include "Framework/pch.h"
#include "Game/States/TitleScene/TitleMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"

// �R���X�g���N�^
TitleMainState::TitleMainState()
{
	// ���̓}�l�[�W���[�̃C���X�^���X�����
	m_inputManager = InputManager::GetInstance();
}

// �f�X�g���N�^
TitleMainState::~TitleMainState()
{

}

// ����������
void TitleMainState::OnStateEnter(StateController* stateController)
{
	
}

// �X�V����
void TitleMainState::OnStateUpdate(StateController* stateController, const float& deltaTime)
{
	// �X�y�[�X����͂�����v���C�V�[���ֈȍ~
	if (m_inputManager->OnKeyDown(InputManager::Keys::Space))
	{
		// �p�����[�^�[�̕ύX
		stateController->SetParameter("FadeOUT", true);
	}
}

// �I������
void TitleMainState::OnStateExit(StateController* stateController)
{

}