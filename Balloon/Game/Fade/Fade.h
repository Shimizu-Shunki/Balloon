#pragma once
#include <future>
#include "Shader/2DSpriteShader/Sprite2DShader.h"
#include "Scenes/SceneManager/SceneManager.h"

class SceneManager;
class Sprite2DShader;


class Fade
{
public:

	bool GetIsActive() const { return m_isActive; }

public:

	// �R���X�g���N�^
	Fade();
	// �f�X�g���N�^
	~Fade();

public:

	// �t�F�[�h�C������
	template <typename T>
	void ChangeSceneFadeIN(float duration) // �C�ӂ̕b���������œn��
	{
		// �t�F�[�h�������Ȃ珈�����I��
		if (m_isActive)
			return;

		m_isActive = true; // �t�F�[�h�����J�n
		m_sprite->SetRuleProgress(0.0f); // �A���t�@�l���V�F�[�_�[�ɐݒ�

		// ���̃V�[���̃��[�h������
		//m_sceneManager->NextSceneLoade<T>([this]() {
		//	// �V�[�����[�h��̏����������ɋL�q�\
		//});
		

		// �񓯊��^�X�N���N��
		m_future = std::async(std::launch::async, [this, duration]()
		{
			// �����A���t�@�l�i���S�s�����j
			float alpha = 0.0f;
			// �A���t�@�l�̑����ʁistep �𓮓I�Ɍv�Z�j
			const float step = 1.0f / (duration / 0.016f);

			while (alpha < 1.0f)
			{
				alpha += step;
				if (alpha > 1.0f)
				{
					alpha = 1.0f;
				}

				m_sprite->SetRuleProgress(alpha); // �A���t�@�l���V�F�[�_�[�ɐݒ�
				// �t���[���ҋ@ (16ms �� 60FPS����)
				std::this_thread::sleep_for(std::chrono::milliseconds(16));
			}

			// �t�F�[�h���A�N�e�B�u
			m_isActive = false;

			// �V�[����؂�ւ���
			//m_sceneManager->ChageScene();
		});
	}


	// �t�F�[�h�A�E�g����
	//bool FadeOUT();

	void FadeOUT(float duration)
	{
		// �t�F�[�h�������Ȃ珈�����I��
		if (m_isActive)
			return;

		m_isActive = true; // �t�F�[�h�����J�n
		m_sprite->SetRuleProgress(1.0f); // �A���t�@�l���V�F�[�_�[�ɐݒ�

		// �񓯊��^�X�N���N��
		m_future = std::async(std::launch::async, [this, duration]()
		{
			// �����A���t�@�l�i���S�s�����j
			float alpha = 1.0f;
			// �A���t�@�l�̌����ʁistep �𓮓I�Ɍv�Z�j
			const float step = 1.0f / (duration / 0.016f);

			while (alpha > 0.0f)
			{
				alpha -= step;
				if (alpha < 0.0f)
				{
					alpha = 0.0f;
				}

				m_sprite->SetRuleProgress(alpha); // �A���t�@�l���V�F�[�_�[�ɐݒ�
				// �t���[���ҋ@ (16ms �� 60FPS����)
				std::this_thread::sleep_for(std::chrono::milliseconds(16));
			}

			// �t�F�[�h���A�N�e�B�u
			m_isActive = false;
		});
	}


	// �`�悷��
	void Render();

	private:

		// �V�[���}�l�[�W���[
		SceneManager* m_sceneManager;
		// �t�F�[�h�p�e�N�X�`��
		std::unique_ptr<Sprite2DShader> m_sprite;
		// �񓯊��^�X�N�Ǘ��p
		std::future<void> m_future;
		
		// �t�F�[�h����
		float m_fadeTime;
		// �t�F�[�h�A�N�e�B�u
		bool m_isActive;


};