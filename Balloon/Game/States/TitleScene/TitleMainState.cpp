#include "Framework/pch.h"
#include "Game/States/TitleScene/TitleMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Message/SceneMessenger.h"

// �R���X�g���N�^
TitleMainState::TitleMainState()
{
	// ���̓}�l�[�W���[�̃C���X�^���X�����
	m_inputManager = InputManager::GetInstance();
	m_sceneMessenger = SceneMessenger::GetInstance();
}

// �f�X�g���N�^
TitleMainState::~TitleMainState()
{

}

// ����������
void TitleMainState::PreUpdate()
{
	
}

// �X�V����
void TitleMainState::Update(const float& deltaTime)
{
	// �X�y�[�X����͂�����v���C�V�[���ֈȍ~
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// ���b�Z�[�W�𑗐M
		m_sceneMessenger->Dispatch(Message::SceneMessageID::FADE_OUT);
	}
}

// �I������
void TitleMainState::PostUpdate()
{

}