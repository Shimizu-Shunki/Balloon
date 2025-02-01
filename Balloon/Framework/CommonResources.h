/**********************************************
 *
 *  CommonResources.h
 *  各リソースのラップクラス（シングルトン）
 *
 *  製作者：清水駿希
 *  制作日：2025/01/25
 *
 **********************************************/
#pragma once
#include "Framework/pch.h"
#include "DeviceResources.h"
#include "StepTimer.h"
#include "CommonStates.h"
#include "Framework/AudioManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Framework/Resources.h"
#include "Framework/RenderManager.h"
#include "Framework/CameraManager.h"

class CommonResources
{
public:
	// 設定　取得
	// デバイスリソース
	void SetDeviceResources(DX::DeviceResources* deviceResources) { m_deviceResources = deviceResources; }
	DX::DeviceResources* GetDeviceResources() { return m_deviceResources; }
	//	タイマー
	void SetStepTimer(DX::StepTimer* stepTimer) { m_stepTimer = stepTimer; }
	DX::StepTimer* GetStepTimer() { return m_stepTimer; }
	//	コモンステート
	void SetCommonStates(DirectX::CommonStates* commonStates) { m_commonStates = commonStates; }
	DirectX::CommonStates* GetCommonStates() { return m_commonStates; }
	//	オーディオマネージャー
	void SetAudioManager(AudioManager* audioManager) { m_audioManager =  audioManager; }
	AudioManager* GetAudioManager() { return m_audioManager; }
	//	入力マネージャー
	void SetInputManager(InputManager* inputManager) { m_inputManager = inputManager; }
	InputManager* GetInputManager() { return m_inputManager; }
	//	シーンマネージャー
	void SetSceneManager(SceneManager* sceneManager) { m_sceneManager = sceneManager; }
	SceneManager* GetSceneManager() { return m_sceneManager; }
	// リソース
	void SetResources(Resources* resources) { m_resources = resources; }
	Resources* GetResources() { return m_resources; }
	// 描画マネージャー
	void SetRenderManager(RenderManager* renderManager) { m_renderManager = renderManager; }
	RenderManager* GetRenderManager() { return m_renderManager; }
	// カメラマネージャー
	void SetCameraManager(CameraManager* cameraManager) { m_cameraManager = cameraManager; }
	CameraManager* GetCameraManager() { return m_cameraManager; }

	// スクリーンサイズ
	void GetScreenSize(int& width, int& height) const { width = m_screenW; height = m_screenH; }
	void SetScreenSize(const int& width, const int& height) { m_screenW = width; m_screenH = height; }
	// ビュー行列
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& view) { m_view = view; }
	const DirectX::SimpleMath::Matrix& GetViewMatrix() { return m_view; };
	// 射影行列
	void SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projection) { m_projection = projection; }
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() { return m_projection; };

private:
	//	コンストラクタ
	CommonResources() :
		m_deviceResources(nullptr),
		m_stepTimer(nullptr),
		m_commonStates(nullptr),
		m_audioManager(nullptr),
		m_inputManager(nullptr),
		m_sceneManager(nullptr),
		m_resources(nullptr),
		m_renderManager(nullptr),
		m_screenW(0),
		m_screenH(0),
		m_view{},
		m_projection{}
	{};
	//	デストラクタ
	~CommonResources() = default;

public:
	CommonResources(const CommonResources&) = delete;             // コピー禁止
	CommonResources& operator=(const CommonResources&) = delete;  // コピー代入禁止
	CommonResources(const CommonResources&&) = delete;            // ムーブ禁止
	CommonResources& operator=(const CommonResources&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static CommonResources* GetInstance()
	{
		static CommonResources instance;
		return &instance;
	}

private:

	// デバイスリソース
	DX::DeviceResources* m_deviceResources;
	// タイマー
	DX::StepTimer* m_stepTimer;
	// リソース
	Resources* m_resources;
	// コモンステート
	DirectX::CommonStates* m_commonStates;
	// オーディオマネージャー
	AudioManager* m_audioManager;
	// 入力マネージャー
	InputManager* m_inputManager;
	// シーンマネージャー
	SceneManager* m_sceneManager;
	// 描画マネージャー
	RenderManager* m_renderManager;
	// カメラマネージャー
	CameraManager* m_cameraManager;

	// スクリーンサイズ
	int m_screenW, m_screenH;
	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;
};