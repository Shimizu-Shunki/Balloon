// ============================================
// 
// �t�@�C����: StageSelectMainState.cpp
// �T�v: �X�e�[�W�Z���N�g�V�[���̃��C�������X�e�[�g
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/StageSelectScene/StageSelectMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Message/SceneMessenger.h"
#include "Framework/AudioManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
StageSelectMainState::StageSelectMainState()
{
	// ���̓}�l�[�W���[�̃C���X�^���X�����
	m_inputManager = InputManager::GetInstance();
}

/// <summary>
/// ��������
/// </summary>
void StageSelectMainState::PreUpdate()
{
	
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void StageSelectMainState::Update(const float& deltaTime)
{
	(void)deltaTime;

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
		// SE���Đ�
		AudioManager::GetInstance()->PlaySE(XACT_WAVEBANK_SOUNDS_CANCEL,0.2f);
		// ���b�Z�[�W�𑗐M
		SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_MENU_SCENE);
	}

	// ESC�L�[�Ń��j���[�V�[���ֈړ�
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT);
	}
}

/// <summary>
/// �I������
/// </summary>
void StageSelectMainState::PostUpdate()
{

}