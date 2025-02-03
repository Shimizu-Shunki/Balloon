#pragma once
#include "Interface/IScene.h"

#include <future>
#include <queue>
#include "StepTimer.h"

// �e�V�[���̃w�b�_�[�t�@�C��
//#include "Scenes/TitleScene/TitleScene.h"
//#include "Scenes/PlayScene/PlayScene.h"
//#include "Scenes/ResultScene/ResultScene.h"
//#include "Scenes/HomeScene/HomeScene.h"
#include "Game/Scenes/Header/PlayScene.h"

class IScene;
class CommonResources;

class SceneManager
{
public:
	// �����t���[���̎��ɃV�[����ύX����
	void ChageScene() { m_isChange = true; }
	// �`�F�b�N�`�F���W�V�[��
	void CheckChageScene();

public:
	
	// �V�[����񓯊��ŏ���
	template <typename T>
	void PrepareScene() {
		// �񓯊��^�X�N�ŃV�[��������
		m_future = std::async(std::launch::async, [this]() {

			// �V�[���̍쐬�Ə�����
			auto newScene = std::make_unique<T>();
			newScene->Initialize(); 
		});
	}


	template <typename T>
	void NextSceneLoade()
	{
		// ���̃V�[�����쐬
		std::unique_ptr<IScene> newScene = std::make_unique<PlayScene>();
		newScene->Initialize();
		// ���̃V�[��������������
		m_nextScene = std::move(newScene);
		
	}

private:
	//	�R���X�g���N�^
	SceneManager();
	//	�f�X�g���N�^
	~SceneManager() = default;
public:
	SceneManager(const SceneManager&) = delete;             // �R�s�[�֎~
	SceneManager& operator=(const SceneManager&) = delete;  // �R�s�[����֎~
	SceneManager(const SceneManager&&) = delete;            // ���[�u�֎~
	SceneManager& operator=(const SceneManager&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}

public:

	// ����������
	void Initialize();
	// �X�V����
	void Update(DX::StepTimer const& timer);
	// �`�揈��
	void Render();
	// �I������
	void Finalize();
private:

	// ���L���\�[�X
	CommonResources* m_commonResources;

	// �V�[��
	std::unique_ptr<IScene> m_currentScene;
	// ���̃V�[��
	std::unique_ptr<IScene> m_nextScene;

	// �V�[���؂�ւ��t���O
	bool m_isChange;

	// �񓯊��^�X�N�Ǘ��p
	std::future<void> m_future;
};