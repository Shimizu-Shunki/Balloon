// ============================================
// 
// �t�@�C����: TitleMainState.cpp
// �T�v: �^�C�g���V�[���̃��C�������X�e�[�g
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/TitleScene/TitleMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Message/SceneMessenger.h"
#include "Framework/AudioManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleMainState::TitleMainState()
{
	// ���̓}�l�[�W���[�̃C���X�^���X�����
	m_inputManager = InputManager::GetInstance();
	m_sceneMessenger = SceneMessenger::GetInstance();
}

/// <summary>
/// ��������
/// </summary>
void TitleMainState::PreUpdate()
{
	
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void TitleMainState::Update(const float& deltaTime)
{
	(void)deltaTime;

	// �X�y�[�X����͂�����v���C�V�[���ֈȍ~
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// SE���Đ�
		AudioManager::GetInstance()->PlaySE(XACT_WAVEBANK_SOUNDS_STARTBUTTON);
		
		// ���b�Z�[�W�𑗐M
		m_sceneMessenger->Dispatch(Message::SceneMessageID::FADE_OUT);
	}
}

/// <summary>
/// �I������
/// </summary>
void TitleMainState::PostUpdate()
{

}