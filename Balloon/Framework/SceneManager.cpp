// ============================================
// 
// �t�@�C����: SceneManager.h
// �T�v: �e�V�[�����Ǘ�����N���X
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Framework/SceneManager.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/TweenManager.h"
#include "Game/Game.h"

// �e�V�[��
#include "Game/Scenes/Header/PlayScene.h"
#include "Game/Scenes/Header/TitleScene.h"
#include "Game/Scenes/Header/PlayScene.h"
#include "Game/Scenes/Header/DebugScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager()
	:
	m_currentScene{},
	m_nextScene{},
	m_isChange{},
	m_future{}
{
	// ���L���\�[�X�̃C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();
	// TweenManager�̃C���X�^���X���擾����
	m_tweenManager = TweenManager::GetInstance();
}

/// <summary>
/// ����������
/// </summary>
void SceneManager::Initialize()
{
	// �����V�[���̍쐬
	m_currentScene = std::make_unique<PlayScene>();
	// �����V�[���̏�����
	m_currentScene->Initialize();

	// �`��}�l�[�W���[�̃��f���B�������i�K����ړ�
	m_commonResources->GetRenderManager()->SwitchRenderbleObjects();
	// �J�����������i�K�̂��̂����C���ɐ؂�ւ���
	m_commonResources->GetCameraManager()->SwitchCameras();

	// �����V�[���̃X�^�[�g����
	m_currentScene->Start();

	m_isChange = false;
	m_isExitGame = false;
}

/// <summary>
/// �X�V����
/// </summary>
void SceneManager::Update()
{
	if (m_currentScene != nullptr)
		m_currentScene->Update();
}
/// <summary>
/// �`�揈��
/// </summary>
void SceneManager::Render()
{
	if (m_currentScene != nullptr)
		m_currentScene->Render();
}
/// <summary>
/// �I������
/// </summary>
void SceneManager::Finalize()
{
	if (m_currentScene != nullptr)
		m_currentScene->Finalize();
}

/// <summary>
/// �V�[���؂�ւ�
/// </summary>
bool SceneManager::CheckChageScene()
{
	// �Q�[���I���̏ꍇ
	if (m_isExitGame)
	{
		return false;
	}

	// �V�[���؂�ւ��t���O���I���̏ꍇ
	if (m_isChange)
	{
		// �O�̃V�[���̏I���������s��
		m_currentScene->Finalize();
		// �O�̃V�[�����폜����
		m_currentScene.reset();
		// ���̃V�[��������
		m_currentScene = std::move(m_nextScene);

		// �`��I�u�W�F�N�g�����̃V�[���̕��ɐ؂�ւ���
		m_commonResources->GetRenderManager()->SwitchRenderbleObjects();
		// �J���������̃V�[���̕��ɐ؂�ւ���
		m_commonResources->GetCameraManager()->SwitchCameras();

		// �����蔻������̃V�[���̕��ɐ؂�ւ���
		
		// �O��Tween�����ׂĒ�~����
		// m_tweenManager->Stop();

		// ���̃V�[���X�^�[�g����
		m_currentScene->Start();

		// �t���O����������
		m_isChange = false;
	}

	return true;
}