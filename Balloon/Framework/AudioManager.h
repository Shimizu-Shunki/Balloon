#pragma once
#include <future>
#include "Sounds.h"


class AudioManager
{
	// BGM�̍Đ�
	// SE�̍Đ�

	// BGM�̍Đ��@�t�F�[�h�A�E�g
	// BGM�̒�~�@�t�F�[�h�C��

public :

	// �f�X�g���N�^
	~AudioManager();

	// InputManager�N���X�̃C���X�^���X���擾����
	static AudioManager* const GetInstance();
	// �}�X�^�[���ʂ�ݒ肷��
	void SetMasterVolume(const float& volume);
	// SE�̉��ʂ�ݒ肷��
	void SetSeVolume(const float& volume);
	// BGM�̉��ʂ�ݒ肷��
	void SetBgmVolume(const float& volume);


public:
	// ����������
	void Initialize();
	// �X�V����
	void Update(DX::StepTimer const& timer);

	// �v���CBGM
	void PlayFadeInBgm(XACT_WAVEBANK_SOUNDS bgmName, float fadeTime = 1.0f);
	// �X�g�b�vBGM
	void StopFadeOutBgm(float fadeTime = 1.0f);

	// SE���Đ�
	void PlaySE();

private:
	// �R���X�g���N�^
	AudioManager();

	


private:
	// �^�C�}�[
	DX::StepTimer m_stepTimer;

	using BgmMap = std::unordered_map<XACT_WAVEBANK_SOUNDS, std::unique_ptr<DirectX::SoundEffectInstance>>;

	// AudioManager�N���X�̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<AudioManager> m_audioManager;

	// �I�[�f�B�I�G���W��
	std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
	// BGM�̃o���N
	std::unique_ptr<DirectX::WaveBank> m_waveBank;
	// BGM�̊i�[
	BgmMap m_bgms;
	// BGM�̃C���X�^���X
	DirectX::SoundEffectInstance* m_currentBGM;

	// �t�F�[�h�t���O
	bool m_isActive;
	// SE�t���O
	bool m_isSE;
	// �^�C��
	float m_timer;
	// �t�F�[�h�^�C��
	float m_fadeTime;
	// ���݂̉���
	float m_currentValue;

	std::unique_ptr<DirectX::SoundEffect> m_soundEffectBGM;
	

	std::unique_ptr<DirectX::SoundEffect> m_soundEffectSE;
	std::unique_ptr<DirectX::SoundEffectInstance> m_soundEffectInstanceSE;
	// �}�X�^�[����
	float m_masterVolume;
	// SE�̉���
	float m_seVolume;
	// BGM�̉���
	float m_bgmVolume;

	// �񓯊������̊Ǘ�
	std::future<void> fadeFuture; 
};