// ============================================
// 
// �t�@�C����: GameClearMainState.cpp
// �T�v: �Q�[���N���A�V�[���̃��C�������X�e�[�g
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/GameClearScene/GameClearMainState.h"
#include "Framework/AudioManager.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Message/SceneMessenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameClearMainState::GameClearMainState()
{
	// ���̓}�l�[�W���[�̃C���X�^���X�����
	m_inputManager = InputManager::GetInstance();
}


/// <summary>
/// ��������
/// </summary>
void GameClearMainState::PreUpdate()
{
	
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void GameClearMainState::Update(const float& deltaTime)
{
	(void)deltaTime;

	// Z����͂�����v���C�V�[���ֈȍ~
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// SE���Đ�
		AudioManager::GetInstance()->PlaySE(XACT_WAVEBANK_SOUNDS_MOVE,0.2f);
		// ���b�Z�[�W�𑗐M
		SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT);
	}
}

/// <summary>
/// �I������
/// </summary>
void GameClearMainState::PostUpdate()
{

}