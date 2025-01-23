#pragma once
#include <Mouse.h>
#include <Keyboard.h>
#include <GamePad.h>


class InputManager
{
private:
	
		
public:
	InputManager(const HWND& window);
	~InputManager() = default;

	// InputManager�N���X�̃C���X�^���X���쐬����
	static InputManager* const CrateInstance(const HWND& window = nullptr);
	// InputManager�N���X�̃C���X�^���X���擾����
	static InputManager* const GetInstance() { return m_input_manager.get(); };

	void Update();

	// �}�E�X�̏�Ԃ�ύX
	void SetMouseMode(DirectX::Mouse::Mode mouse_mode) { m_mouse->SetMode(mouse_mode); }

	// �}�E�X�X�e�[�g���擾����
	const DirectX::Mouse::State& GetMouseState() const
	{
		return m_mouse_state;
	}
	// �}�E�X�̃{�^���X�e�[�g�g���b�J�[���擾����
	const std::unique_ptr<DirectX::Mouse::ButtonStateTracker>& GetMouseTracker() const
	{
		return m_mouse_state_tracker;
	}
	// �L�[�{�[�h�X�e�[�g���擾����
	const DirectX::Keyboard::State& GetKeyboardState() const
	{
		return m_keyboard_state;
	}
	// �L�[�{�[�h�̃X�e�[�g�g���b�J�[���擾����
	const DirectX::Keyboard::KeyboardStateTracker* GetKeyboardTracker() const
	{
		return m_keyboard_state_tracker.get();
	}

	// �Q�[���p�b�h�擾����
	DirectX::GamePad* GetGamePad()
	{
		return m_gamepad.get();
	}

	// �Q�[���p�b�h�X�e�[�g���擾
	const DirectX::GamePad::State& GetGamePadState() const
	{
		return m_GamePadState;
	}
	// �Q�[���p�b�g�X�e�[�g�g���b�J�[���擾����
	const DirectX::GamePad::ButtonStateTracker* GetButtonStateTracker() const
	{
		return m_gamePadStateTracker.get();
	}

private:
	//InputManager�N���X�̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<InputManager> m_input_manager;

	// �}�E�X
	std::unique_ptr<DirectX::Mouse> m_mouse;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouse_state_tracker;
	DirectX::Mouse::State m_mouse_state;

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboard_state_tracker;
	DirectX::Keyboard::State m_keyboard_state;

	// �p�b�h
	std::unique_ptr<DirectX::GamePad> m_gamepad;
	std::unique_ptr<DirectX::GamePad::ButtonStateTracker> m_gamePadStateTracker;
	DirectX::GamePad::State m_GamePadState;
};