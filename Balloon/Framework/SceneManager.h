// ============================================
// 
// �t�@�C����: SceneManager.h
// �T�v: SceneManager.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include <future>
#include "Interface/IScene.h"

class IScene;
class CommonResources;
class TweenManager;

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
			m_nextScene = std::make_unique<T>();
			m_nextScene->Initialize();
		});
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
	void Update();
	// �`�揈��
	void Render();
	// �I������
	void Finalize();
private:

	// ���L���\�[�X
	CommonResources* m_commonResources;
	// TweenManager
	TweenManager* m_tweenManager;

	// �V�[��
	std::unique_ptr<IScene> m_currentScene;
	// ���̃V�[��
	std::unique_ptr<IScene> m_nextScene;

	// �V�[���؂�ւ��t���O
	bool m_isChange;

	// �񓯊��^�X�N�Ǘ��p
	std::future<void> m_future;
};