#pragma once
#include <future>
#include "Game/Material/SpriteMaterial.h"
#include "Game/Material/Buffers.h"
#include "Framework/SceneManager.h"
#include "Framework/Resources.h"

class CommonResources;

class Fade
{
public:

	bool GetIsActive() const { return m_isActive; }

public:

	// �R���X�g���N�^
	Fade();
	// �f�X�g���N�^
	~Fade();

	// �X�V����
	void Update();

public:

	// �t�F�[�h�C������
	void FadeIN(float duration);
	// �t�F�[�h�A�E�g�����@�V�[���؂�ւ��t��
	template <typename T>
	void ChangeSceneFadeOUT(float duration)
	{
		// �t�F�[�h�������Ȃ� true ��Ԃ�
		if (m_isActive) return;

		// ���̃V�[���̏�������񓯊��Ŏ��s
		m_sceneManager->NextSceneLoade<T>();

		// �t�F�[�h���Ԃ�ݒ�
		m_duration = duration;

		// ���[���摜�̐i�s�x��������
		m_constBuffer.ruleProgress = 0.0f;
		// ���[���摜�̔��]�����Ȃ�
		m_constBuffer.ruleInverse = 0;

		// �X�^�[�g�i�s�x
		m_startProgress = 0.0f;
		// �G���h�i�s�x
		m_endProgress = 1.0f;

		// �t�F�[�h�������A�N�e�B�u�ɂ���
		m_isActive = true;
	}

	// �`�悷��
	void Render();

	private:

		// ���L���\�[�X
		CommonResources* m_commonResources;

		// �R���e�L�X�g
		ID3D11DeviceContext1* m_context;

		// �o�b�t�@
		ConstBuffer m_constBuffer;
		
		// �摜�T�C�Y
		int m_textureSizeW, m_textureSizeH;

		// �V�[���}�l�[�W���[
		SceneManager* m_sceneManager;
		// �t�F�[�h�p�}�e���A��
		std::unique_ptr<SpriteMaterial> m_spriteMaterial;
		// �񓯊��^�X�N�Ǘ��p
		std::future<void> m_future;

		// �t�F�[�h����
		float m_duration;
		// ���[���摜�̌��݂̐i�s�x
		float m_curentRuleProgress;
		// ���݂̌o�ߎ���
		float m_curentTime;
		// �X�^�[�g�@�G���h�i�s�x
		float m_startProgress, m_endProgress;
		// �t�F�[�h�A�N�e�B�u
		bool m_isActive;

};