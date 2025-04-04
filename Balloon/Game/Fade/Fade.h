#pragma once
#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"

class CommonResources;
class SceneManager;
class Image;
class IMaterial;
class Transform;
class DefaultUi;

class Fade
{
public:

	bool GetIsActive() const { return m_isActive; }
	
	Transform* GetTransform() const { return m_transform.get(); }

public:

	// �R���X�g���N�^
	Fade();
	// �f�X�g���N�^
	~Fade() = default;

	// ����������
	void Initialize();
	// �X�V����
	void Update();

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

		auto material = dynamic_cast<DefaultUi*>(m_material.get());

		// ���[���摜�̐i�s�x��������
		material->SetRuleProgress(0.0f);
		// ���[���摜�̔��]�����Ȃ�
		material->SetRuleInverse(0.0f);

		// �X�^�[�g�i�s�x
		m_startProgress = 0.0f;
		// �G���h�i�s�x
		m_endProgress = 1.0f;

		// �t�F�[�h�������A�N�e�B�u�ɂ���
		m_isActive = true;
	}

	void ExitGameFadeOUT(float duration)
	{
		// �t�F�[�h�������Ȃ� true ��Ԃ�
		if (m_isActive) return;

		// �t�F�[�h���Ԃ�ݒ�
		m_duration = duration;

		auto material = dynamic_cast<DefaultUi*>(m_material.get());

		// ���[���摜�̐i�s�x��������
		material->SetRuleProgress(0.0f);
		// ���[���摜�̔��]�����Ȃ�
		material->SetRuleInverse(0.0f);

		// �X�^�[�g�i�s�x
		m_startProgress = 0.0f;
		// �G���h�i�s�x
		m_endProgress = 1.0f;

		// �t�F�[�h�������A�N�e�B�u�ɂ���
		m_isActive = true;

		m_isExitGame = true;
	}

private:
	// �}�e���A���̏���������
	void InitialMaterial(int width, int height);



private:

	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �R���e�L�X�g
	ID3D11DeviceContext1* m_context;
	// �V�[���}�l�[�W���[
	SceneManager* m_sceneManager;

	// �g�����X�t�H�[��
	std::unique_ptr<Transform> m_transform;
	// Image
	std::unique_ptr<Image> m_image;
	// �}�e���A��
	std::unique_ptr<IMaterial> m_material;

	// �e�N�X�`���T�C�Y
	int m_textureSizeW, m_textureSizeH;
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

	bool m_isExitGame;
};