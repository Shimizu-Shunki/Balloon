#include "Framework/pch.h"
#include "Game/States/PlayScene/PlayMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Player/Header/Player.h"
#include "Game/Enemy/Enemy.h"

// �R���X�g���N�^
PlayMainState::PlayMainState(Player* player, std::vector<Enemy*> enemys)
	:
	m_player(player),
	m_enemys(enemys)
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
	if (m_inputManager->OnKeyDown(InputManager::Keys::C))
	{
		// �p�����[�^�[�̕ύX
		stateController->SetParameter("FadeOUT", 1);
	}
	else if (m_inputManager->OnKeyDown(InputManager::Keys::F))
	{
		// �p�����[�^�[�̕ύX
		stateController->SetParameter("FadeOUT", 2);
	}

	if (m_player->GetTransform()->GetLocalPosition().y <= -2.0f)
	{
		// �p�����[�^�[�̕ύX
		stateController->SetParameter("FadeOUT", 2);
	}

	for (auto enemy : m_enemys)
	{
		if (enemy->GetTransform()->GetLocalPosition().y >= -1.0f)
		{
			return;
		}
	}

	// �p�����[�^�[�̕ύX
	stateController->SetParameter("FadeOUT", 1);
}

// �I������
void PlayMainState::OnStateExit(StateController* stateController)
{

}