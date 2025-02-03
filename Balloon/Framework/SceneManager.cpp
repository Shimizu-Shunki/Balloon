#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Framework/SceneManager.h"
#include "Interface/IScene.h"
#include "Game/Scenes/Header/PlayScene.h"
#include "Game/Scenes/Header/TitleScene.h"
#include "Game/Scenes/Header/PlayScene.h"

SceneManager::SceneManager()
	:
	m_nextScene{}
{
	m_commonResources = CommonResources::GetInstance();
}

void SceneManager::Initialize()
{
	// �����V�[���̍쐬
	m_currentScene = std::make_unique<TitleScene>();
	// �����V�[���̏�����
	m_currentScene->Initialize();

	// �`��}�l�[�W���[�̃��f���B�������i�K����ړ�
	m_commonResources->GetRenderManager()->CommitPendingDrawables();

	// �����V�[���̃X�^�[�g����
	m_currentScene->Start();

	m_isChange = false;
}

void SceneManager::Update(DX::StepTimer const& timer)
{
	if (m_currentScene != nullptr)
		m_currentScene->Update();
}

void SceneManager::Render()
{
	if (m_currentScene != nullptr)
		m_currentScene->Render();
}

void SceneManager::Finalize()
{
	if (m_currentScene != nullptr)
		m_currentScene->Finalize();
}


void SceneManager::CheckChageScene()
{
	if (m_isChange)
	{
		// �O�̃V�[�����폜����
		m_currentScene.reset();
		// ���̃V�[��������
		m_currentScene = std::move(m_nextScene);
		// ���̃V�[���X�^�[�g����
		m_currentScene->Start();
		// �t���O����������
		m_isChange = false;
	}
}