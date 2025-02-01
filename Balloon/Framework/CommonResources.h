/**********************************************
 *
 *  CommonResources.h
 *  �e���\�[�X�̃��b�v�N���X�i�V���O���g���j
 *
 *  ����ҁF�����x��
 *  ������F2025/01/25
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
	// �ݒ�@�擾
	// �f�o�C�X���\�[�X
	void SetDeviceResources(DX::DeviceResources* deviceResources) { m_deviceResources = deviceResources; }
	DX::DeviceResources* GetDeviceResources() { return m_deviceResources; }
	//	�^�C�}�[
	void SetStepTimer(DX::StepTimer* stepTimer) { m_stepTimer = stepTimer; }
	DX::StepTimer* GetStepTimer() { return m_stepTimer; }
	//	�R�����X�e�[�g
	void SetCommonStates(DirectX::CommonStates* commonStates) { m_commonStates = commonStates; }
	DirectX::CommonStates* GetCommonStates() { return m_commonStates; }
	//	�I�[�f�B�I�}�l�[�W���[
	void SetAudioManager(AudioManager* audioManager) { m_audioManager =  audioManager; }
	AudioManager* GetAudioManager() { return m_audioManager; }
	//	���̓}�l�[�W���[
	void SetInputManager(InputManager* inputManager) { m_inputManager = inputManager; }
	InputManager* GetInputManager() { return m_inputManager; }
	//	�V�[���}�l�[�W���[
	void SetSceneManager(SceneManager* sceneManager) { m_sceneManager = sceneManager; }
	SceneManager* GetSceneManager() { return m_sceneManager; }
	// ���\�[�X
	void SetResources(Resources* resources) { m_resources = resources; }
	Resources* GetResources() { return m_resources; }
	// �`��}�l�[�W���[
	void SetRenderManager(RenderManager* renderManager) { m_renderManager = renderManager; }
	RenderManager* GetRenderManager() { return m_renderManager; }
	// �J�����}�l�[�W���[
	void SetCameraManager(CameraManager* cameraManager) { m_cameraManager = cameraManager; }
	CameraManager* GetCameraManager() { return m_cameraManager; }

	// �X�N���[���T�C�Y
	void GetScreenSize(int& width, int& height) const { width = m_screenW; height = m_screenH; }
	void SetScreenSize(const int& width, const int& height) { m_screenW = width; m_screenH = height; }
	// �r���[�s��
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& view) { m_view = view; }
	const DirectX::SimpleMath::Matrix& GetViewMatrix() { return m_view; };
	// �ˉe�s��
	void SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projection) { m_projection = projection; }
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix() { return m_projection; };

private:
	//	�R���X�g���N�^
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
	//	�f�X�g���N�^
	~CommonResources() = default;

public:
	CommonResources(const CommonResources&) = delete;             // �R�s�[�֎~
	CommonResources& operator=(const CommonResources&) = delete;  // �R�s�[����֎~
	CommonResources(const CommonResources&&) = delete;            // ���[�u�֎~
	CommonResources& operator=(const CommonResources&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static CommonResources* GetInstance()
	{
		static CommonResources instance;
		return &instance;
	}

private:

	// �f�o�C�X���\�[�X
	DX::DeviceResources* m_deviceResources;
	// �^�C�}�[
	DX::StepTimer* m_stepTimer;
	// ���\�[�X
	Resources* m_resources;
	// �R�����X�e�[�g
	DirectX::CommonStates* m_commonStates;
	// �I�[�f�B�I�}�l�[�W���[
	AudioManager* m_audioManager;
	// ���̓}�l�[�W���[
	InputManager* m_inputManager;
	// �V�[���}�l�[�W���[
	SceneManager* m_sceneManager;
	// �`��}�l�[�W���[
	RenderManager* m_renderManager;
	// �J�����}�l�[�W���[
	CameraManager* m_cameraManager;

	// �X�N���[���T�C�Y
	int m_screenW, m_screenH;
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;
};