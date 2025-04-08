#include "Framework/pch.h"
#include "Game/States/StageSelectScene/StageSelectMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Message/SceneMessenger.h"

// �R���X�g���N�^
StageSelectMainState::StageSelectMainState()
{
	// ���̓}�l�[�W���[�̃C���X�^���X�����
	m_inputManager = InputManager::GetInstance();
}

// �f�X�g���N�^
StageSelectMainState::~StageSelectMainState()
{

}

// ����������
void StageSelectMainState::PreUpdate()
{
	
}

// �X�V����
void StageSelectMainState::Update(const float& deltaTime)
{
	// ���E�L�[�ŃX�e�[�W��I��
	// ���L�[�������Ƃ�
	if (m_inputManager->OnKeyDown(InputManager::Keys::Left))
	{

	}
	// �E�L�[�������Ƃ�
	if (m_inputManager->OnKeyDown(InputManager::Keys::Right))
	{

	}

	// ESC�L�[�Ń��j���[�V�[���ֈړ�
	if (m_inputManager->OnKeyDown(InputManager::Keys::Escape))
	{
		SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_MENU_SCENE);
	}
}

// �I������
void StageSelectMainState::PostUpdate()
{

}