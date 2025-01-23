#include "pch.h"
#include "Framework/InputManager.h"
#include <Mouse.h>
#include <Keyboard.h>
#include <GamePad.h>

std::unique_ptr<InputManager> InputManager::m_input_manager = nullptr;

// グラフィックスのインスタンスを作成する
InputManager* const InputManager::CrateInstance(const HWND& window)
{
	if (m_input_manager == nullptr)
	{
		// グラフィックスのインスタンスを生成する
		m_input_manager.reset(new InputManager(window));
	}
	// グラフィックスのインスタンスを返す
	return m_input_manager.get();
}

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
InputManager::InputManager(const HWND& window)
	:
	m_mouse_state{},
	m_keyboard_state{},
	m_gamepad{},
	m_gamePadStateTracker{},
	m_GamePadState{}
{
	// マウスを使用できる状態にする
	m_mouse = std::make_unique<DirectX::Mouse>();
	m_mouse->SetWindow(window);
	m_mouse_state_tracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();

	// キーボードを使用できる状態にする
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_keyboard_state_tracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();

	// ゲームパッドを使用できる状態にする
	m_gamepad = std::make_unique<DirectX::GamePad>();
	m_gamePadStateTracker = std::make_unique<DirectX::GamePad::ButtonStateTracker>();
}

//---------------------------------------------------------
// マネージャの持つリソースを更新する
//---------------------------------------------------------
void InputManager::Update()
{
	// マウスの情報を更新する
	m_mouse_state = m_mouse->GetState();
	m_mouse_state_tracker->Update(m_mouse_state);

	// キーボードの情報を更新する
	m_keyboard_state = m_keyboard->GetState();
	m_keyboard_state_tracker->Update(m_keyboard_state);

	// ゲームパッドの情報を更新する
	m_GamePadState = m_gamepad->GetState(0);
	m_gamePadStateTracker->Update(m_GamePadState);
}