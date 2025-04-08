#include "Framework/pch.h"
#include "Game/States/MenuScene/MenuMainState.h"
#include "Framework/StateMachine/StateController.h"
#include "Framework/CommonResources.h"
#include "Game/Message/SceneMessenger.h"

#include "Game/UI/MenuButtonFrameUI.h"
#include "Game/UI/MenuButtonUI.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
MenuMainState::MenuMainState(std::vector<IObject*> buttons)
{
	m_buttons = buttons;
	m_inputManager = CommonResources::GetInstance()->GetInputManager();
	m_buttonIndex = 0;
}

/// <summary>
/// ��������
/// </summary>
/// <param name="stateController">�R���g���[���[</param>
void MenuMainState::PreUpdate()
{
	// Tween�̐ݒ�
	for (int i = 0; i < 3; i++)
	{
		m_buttons[i]->GetTransform()->GetTween()->DOMoveY(360.0f + i * 100.0f, 1.5f).SetDelay(i * 0.5f).SetEase(Tween::EasingType::EaseOutBounce);
		m_buttons[i + 3]->GetTransform()->GetTween()->DOMoveY(365.0f + i * 100.0f, 1.5f).SetDelay(i * 0.5f).SetEase(Tween::EasingType::EaseOutBounce);
	}
}
/// <summary>
/// �X�V����
/// </summary>
/// <param name="stateController">�R���g���[���[</param>
/// <param name="deltaTime">�o�ߎ���</param>
void MenuMainState::Update(const float& deltaTime)
{
	this->SelectButton();
}
/// <summary>
/// �I������
/// </summary>
/// <param name="stateController">�R���g���[���[</param>
void MenuMainState::PostUpdate()
{

}

void MenuMainState::SelectButton()
{
	if (m_inputManager->OnKeyDown(InputManager::Keys::Up))
	{
		m_buttonIndex--;
		if (m_buttonIndex < 0)
			m_buttonIndex = 2;
	}
	else if (m_inputManager->OnKeyDown(InputManager::Keys::Down))
	{
		m_buttonIndex++;
		if (m_buttonIndex > 2)
			m_buttonIndex = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		MenuButtonUI* button = dynamic_cast<MenuButtonUI*>(m_buttons[i]);

		if (i == m_buttonIndex)
			button->SetIsButtonActive(true);
		else
			button->SetIsButtonActive(false);
	}

	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		// ���݂̃{�^���̃I�u�W�F�N�g���擾
		MenuButtonFrameUI* buttonFrame = dynamic_cast<MenuButtonFrameUI*>(m_buttons[m_buttonIndex + 3]);
		// �{�^���t���[�����I���ɂ���
		buttonFrame->SetIsButtonActive(true);

		if (m_buttonIndex == 0)
			SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_STAGE_SCENE);
		else if(m_buttonIndex == 1)
			SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT);
		else
			SceneMessenger::GetInstance()->Dispatch(Message::SceneMessageID::FADE_OUT_EXIT_GAME);

	}
	else if (m_inputManager->OnKeyDown(InputManager::Keys::X))
	{
		// ���݂̃{�^���̃I�u�W�F�N�g���擾
		MenuButtonFrameUI* buttonFrame = dynamic_cast<MenuButtonFrameUI*>(m_buttons[m_buttonIndex + 3]);

		// �{�^���t���[�����I���ɂ���
		buttonFrame->SetIsButtonActive(false);

	}
}

