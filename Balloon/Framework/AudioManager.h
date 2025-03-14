#pragma once
#include <future>
#include "Sounds.h"
#include <Audio.h>



class AudioManager
{
public :
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
	//	�R���X�g���N�^
	AudioManager();
	// �f�X�g���N�^
	~AudioManager();
public:
	AudioManager(const AudioManager&) = delete;             // �R�s�[�֎~
	AudioManager& operator=(const AudioManager&) = delete;  // �R�s�[����֎~
	AudioManager(const AudioManager&&) = delete;            // ���[�u�֎~
	AudioManager& operator=(const AudioManager&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static AudioManager* GetInstance()
	{
		static AudioManager instance;
		return &instance;
	}

private:
	
	using BgmMap = std::unordered_map<XACT_WAVEBANK_SOUNDS, std::unique_ptr<DirectX::SoundEffectInstance>>;

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
	// SE�^�C��
	float m_seTimer;
	// �t�F�[�h�^�C��
	float m_fadeTime;
	// ���݂̉���
	float m_currentValue;

	// �t�F�[�h���̌o�ߎ���
	float m_fadeElapsedTime;
	// �X�^�[�g�{�����[��
	float m_startValueme;
	// �I���{�����[��
	float m_endValueme;


	std::unique_ptr<DirectX::SoundEffect> m_soundEffectSE;
	std::unique_ptr<DirectX::SoundEffectInstance> m_soundEffectInstanceSE;
	// �}�X�^�[����
	float m_masterVolume;
	// SE�̉���
	float m_seVolume;
	// BGM�̉���
	float m_bgmVolume;
};