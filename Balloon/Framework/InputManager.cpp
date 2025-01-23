#include "pch.h"
#include "Framework/InputManager.h"
#include <Mouse.h>
#include <Keyboard.h>
#include <GamePad.h>

std::unique_ptr<InputManager> InputManager::m_input_manager = nullptr;

// �O���t�B�b�N�X�̃C���X�^���X���쐬����
InputManager* const InputManager::CrateInstance(const HWND& window)
{
	if (m_input_manager == nullptr)
	{
		// �O���t�B�b�N�X�̃C���X�^���X�𐶐�����
		m_input_manager.reset(new InputManager(window));
	}
	// �O���t�B�b�N�X�̃C���X�^���X��Ԃ�
	return m_input_manager.get();
}

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
InputManager::InputManager(const HWND& window)
	:
	m_mouse_state{},
	m_keyboard_state{},
	m_gamepad{},
	m_gamePadStateTracker{},
	m_GamePadState{}
{
	// �}�E�X���g�p�ł����Ԃɂ���
	m_mouse = std::make_unique<DirectX::Mouse>();
	m_mouse->SetWindow(window);
	m_mouse_state_tracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();

	// �L�[�{�[�h���g�p�ł����Ԃɂ���
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyboard_state_tracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();

	// �Q�[���p�b�h���g�p�ł����Ԃɂ���
	m_gamepad = std::make_unique<DirectX::GamePad>();
	m_gamePadStateTracker = std::make_unique<DirectX::GamePad::ButtonStateTracker>();
}

//---------------------------------------------------------
// �}�l�[�W���̎����\�[�X���X�V����
//---------------------------------------------------------
void InputManager::Update()
{
	// �}�E�X�̏����X�V����
	m_mouse_state = m_mouse->GetState();
	m_mouse_state_tracker->Update(m_mouse_state);

	// �L�[�{�[�h�̏����X�V����
	m_keyboard_state = m_keyboard->GetState();
	m_keyboard_state_tracker->Update(m_keyboard_state);

	// �Q�[���p�b�h�̏����X�V����
	m_GamePadState = m_gamepad->GetState(0);
	m_gamePadStateTracker->Update(m_GamePadState);
}