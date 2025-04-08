#include "Framework/pch.h"
#include "Game/States/GameOverScene/GameOverMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Message/SceneMessenger.h"

// �R���X�g���N�^
GameOverMainState::GameOverMainState()
{
	// ���̓}�l�[�W���[�̃C���X�^���X�����
	m_inputManager = InputManager::GetInstance();
}

// �f�X�g���N�^
GameOverMainState::~GameOverMainState()
{

}

// ����������
void GameOverMainState::PreUpdate()
{
	
}

// �X�V����
void GameOverMainState::Update(const float& deltaTime)
{
	// �X�y�[�X����͂�����v���C�V�[���ֈȍ~
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// ���b�Z�[�W�𑗐M
		SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT);
	}
}

// �I������
void GameOverMainState::PostUpdate()
{

}