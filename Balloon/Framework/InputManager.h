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

	// InputManagerクラスのインスタンスを作成する
	static InputManager* const CrateInstance(const HWND& window = nullptr);
	// InputManagerクラスのインスタンスを取得する
	static InputManager* const GetInstance() { return m_input_manager.get(); };

	void Update();

	// マウスの状態を変更
	void SetMouseMode(DirectX::Mouse::Mode mouse_mode) { m_mouse->SetMode(mouse_mode); }

	// マウスステートを取得する
	const DirectX::Mouse::State& GetMouseState() const
	{
		return m_mouse_state;
	}
	// マウスのボタンステートトラッカーを取得する
	const std::unique_ptr<DirectX::Mouse::ButtonStateTracker>& GetMouseTracker() const
	{
		return m_mouse_state_tracker;
	}
	// キーボードステートを取得する
	const DirectX::Keyboard::State& GetKeyboardState() const
	{
		return m_keyboard_state;
	}
	// キーボードのステートトラッカーを取得する
	const DirectX::Keyboard::KeyboardStateTracker* GetKeyboardTracker() const
	{
		return m_keyboard_state_tracker.get();
	}

	// ゲームパッド取得する
	DirectX::GamePad* GetGamePad()
	{
		return m_gamepad.get();
	}

	// ゲームパッドステートを取得
	const DirectX::GamePad::State& GetGamePadState() const
	{
		return m_GamePadState;
	}
	// ゲームパットステートトラッカーを取得する
	const DirectX::GamePad::ButtonStateTracker* GetButtonStateTracker() const
	{
		return m_gamePadStateTracker.get();
	}

private:
	//InputManagerクラスのインスタンスへのポインタ
	static std::unique_ptr<InputManager> m_input_manager;

	// マウス
	std::unique_ptr<DirectX::Mouse> m_mouse;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouse_state_tracker;
	DirectX::Mouse::State m_mouse_state;

	// キーボード
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboard_state_tracker;
	DirectX::Keyboard::State m_keyboard_state;

	// パッド
	std::unique_ptr<DirectX::GamePad> m_gamepad;
	std::unique_ptr<DirectX::GamePad::ButtonStateTracker> m_gamePadStateTracker;
	DirectX::GamePad::State m_GamePadState;
};