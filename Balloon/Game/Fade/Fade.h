#pragma once
#include <future>
#include "Game/Material/SpriteMaterial.h"
#include "Game/Material/Buffers.h"
#include "Framework/SceneManager.h"
#include "Framework/Resources.h"
#include "Interface/ISprite.h"

#include "Game/Scenes/Header/PlayScene.h"

class CommonResources;

class Fade : ISprite
{
public:

	bool GetIsActive() const { return m_isActive; }
	
	Transform* GetTransform() const override { return m_transform.get(); }

	SpriteMaterial* GetSpriteMaterial() const override { return m_spriteMaterial.get(); }

public:

	// �R���X�g���N�^
	Fade();
	// �f�X�g���N�^
	~Fade() override = default;

	void Initialize() override;

	// �X�V����
	void Update();

public:

	void Begin() override { m_spriteMaterial->Begin(); }

	void End() override { m_spriteMaterial->End(); }

	// �t�F�[�h�C������
	void FadeIN(float duration);
	// �t�F�[�h�A�E�g�����@�V�[���؂�ւ��t��
	template <typename T>
	void ChangeSceneFadeOUT(float duration)
	{
		// �t�F�[�h�������Ȃ� true ��Ԃ�
		if (m_isActive) return;

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

	

	private:

		// ���L���\�[�X
		CommonResources* m_commonResources;

		std::unique_ptr<Transform> m_transform;

		// �R���e�L�X�g
		ID3D11DeviceContext1* m_context;

		// �o�b�t�@
		ConstBuffer m_constBuffer;
		// ���_�o�b�t�@
		VertexBuffer m_vertexBuffer;
		
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