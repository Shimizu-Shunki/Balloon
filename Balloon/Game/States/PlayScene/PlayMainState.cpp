// ============================================
// 
// �t�@�C����: PlayMainState.cpp
// �T�v: �v���C�V�[���̃��C�������X�e�[�g
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/PlayScene/PlayMainState.h"
#include "Game/Fade/Fade.h"
#include "Framework/InputManager.h"
#include "Game/Player/Header/Player.h"
#include "Game/Enemy/Enemy.h"
#include "Game/Message/SceneMessenger.h"
#include "Game/UI/TimerUI.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayMainState::PlayMainState(std::vector<IObject*> objects)
{
	// ���̓}�l�[�W���[�̃C���X�^���X�����
	m_inputManager = InputManager::GetInstance();
	// �I�u�W�F�N�g���擾����
	m_objects = objects;
}

/// <summary>
/// ��������
/// </summary>
void PlayMainState::PreUpdate()
{
	// �I�u�W�F�N�g��L�����ɂ���
	for (const auto& object : m_objects)
	{
		object->SetIsActive(true);
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void PlayMainState::Update(const float& deltaTime)
{
	(void)deltaTime;

	// �I�u�W�F�N�g�̍X�V���s��
	for (const auto& object : m_objects)
	{
		// �X�V����
		object->Update();
		// Transform�̍X�V����
		object->GetTransform()->Update();

		if (object->GetObjectID() == IObject::ObjectID::TIMER_UI)
		{
			TimerUI* timerUI = dynamic_cast<TimerUI*>(object);
			if (timerUI->GetTime() <= 0.0f)
			{
				SceneMessenger::GetInstance()->Dispatch(Message::FADE_OUT_GAME_OVER_SCENE);
			}
		}
	}

	// �v���C���[����������
	if (m_objects[0]->GetTransform()->GetLocalPosition().y <= -10.0f)
	{
		SceneMessenger::GetInstance()->Dispatch(Message::FADE_OUT_GAME_OVER_SCENE);
	}

	// �G�����ׂė�������
	if (m_objects[1]->GetTransform()->GetLocalPosition().y <= -10.0f &&
		m_objects[2]->GetTransform()->GetLocalPosition().y <= -10.0f)
	{
		SceneMessenger::GetInstance()->Dispatch(Message::FADE_OUT_GAME_CLEAR_SCENE);
	}	
}

/// <summary>
/// �I������
/// </summary>
void PlayMainState::PostUpdate()
{

}