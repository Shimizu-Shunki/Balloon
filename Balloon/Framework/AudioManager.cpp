#include "pch.h"
#include "Framework/AudioManager.h"
#include "Framework/Sounds.h"
#include <Audio.h>
#include <chrono>

std::unique_ptr<AudioManager> AudioManager::m_audioManager = nullptr;

// �I�[�f�B�I�}�l�[�W���[�̃C���X�^���X���쐬����
AudioManager* const AudioManager::GetInstance()
{
	if (m_audioManager == nullptr)
	{
		// �I�[�f�B�I�}�l�[�W���[�̃C���X�^���X�𐶐�����
		m_audioManager.reset(new AudioManager());
	}
	// �I�[�f�B�I�}�l�[�W���[�̃C���X�^���X��Ԃ�
	return m_audioManager.get();
}

// �R���X�g���N�^
AudioManager::AudioManager()
	:
	m_masterVolume{},
	m_seVolume{},
	m_bgmVolume{},
	m_stepTimer{}
{
	m_isActive = false;
	m_isSE = false;
	m_timer = 0.0f;
}

// �f�X�g���N�^
AudioManager::~AudioManager()
{
	m_isActive = false;

	// �I�[�f�B�I�G���W���̌�n��
	if (m_audioEngine)
	{
		m_audioEngine->Suspend();
	}
}

// ����������
void AudioManager::Initialize()
{
	// �I�[�f�B�I�G���W���̃t���O
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AUDIO_ENGINE_FLAGS::AudioEngine_Default;
#ifdef _DEBUG
	eflags |= DirectX::AUDIO_ENGINE_FLAGS::AudioEngine_Debug;
#endif

	// ���ʂ����ׂ�1�ɏ�����
	m_masterVolume = 1.0f;
	m_seVolume     = 1.0f;
	m_bgmVolume    = 1.0f;

	// �I�[�f�B�I�G���W�����쐬����
	m_audioEngine = std::make_unique<DirectX::AudioEngine>(eflags);
	// �}�X�^�[���ʂ̏�����
	m_audioEngine->SetMasterVolume(m_masterVolume);

	// �T�E���h�o���N���쐬����
	m_waveBank = std::make_unique<DirectX::WaveBank>
		(m_audioEngine.get(), L"Resources/Sounds/BGM.xwb");

	// BGM���}�b�v�ɓo�^����
	m_bgms.insert(BgmMap::value_type(XACT_WAVEBANK_SOUNDS_TITLESCENE, m_waveBank->CreateInstance(XACT_WAVEBANK_SOUNDS_TITLESCENE)));
	m_bgms.insert(BgmMap::value_type(XACT_WAVEBANK_SOUNDS_SELECTSCENE, m_waveBank->CreateInstance(XACT_WAVEBANK_SOUNDS_SELECTSCENE)));
	m_bgms.insert(BgmMap::value_type(XACT_WAVEBANK_SOUNDS_PLAYSCENE, m_waveBank->CreateInstance(XACT_WAVEBANK_SOUNDS_PLAYSCENE)));
	m_bgms.insert(BgmMap::value_type(XACT_WAVEBANK_SOUNDS_GAMECLEARSCENE, m_waveBank->CreateInstance(XACT_WAVEBANK_SOUNDS_GAMECLEARSCENE)));
	m_bgms.insert(BgmMap::value_type(XACT_WAVEBANK_SOUNDS_GAMEOVERSCENE, m_waveBank->CreateInstance(XACT_WAVEBANK_SOUNDS_GAMEOVERSCENE)));

	// �C���X�^���X�̏�����
	m_currentBGM = nullptr;
}

void AudioManager::Update(DX::StepTimer const& timer)
{
	// �I�[�f�B�I�G���W�����X�V����
	if (!m_audioEngine->Update())
	{
		// No audio device is active
		if (m_audioEngine->IsCriticalError())
		{
			OutputDebugString(L"AudioEngine Error!\n");
		}
	}


	if (m_isSE)
	{
		m_timer += float(timer.GetElapsedSeconds());
		if (m_timer >= 0.3f)
		{
			m_timer = 0.0f;
			m_soundEffectInstanceSE->Stop();
			m_isSE = false;
		}
	}

	// BGM�̃t�F�[�h����
	if (!m_isActive) return;

	// 1�ɒB����܂ł̑�����
	const float increment = m_bgmVolume / (m_fadeTime / float(m_stepTimer.GetElapsedSeconds()));


	m_currentValue =  + increment * (end - start);

	// ���݂̃{�����[�����X�V
	m_currentValue += increment;

	// ���ʐݒ�
	m_currentBGM->SetVolume(m_currentValue);
	


	// �t�F�[�h���I��������
	if (m_currentValue > m_bgmVolume) {
		m_currentValue = m_bgmVolume;
		// �ŏI���ʂ�ݒ�
		m_currentBGM->SetVolume(m_bgmVolume);
		// ���݂̉��ʂ�������
		m_currentValue = 0.0f;
		// �t�F�[�h���Ԃ�������
		m_fadeTime = 0.0f;
		// �t�F�[�h���A�N�e�B�u
		m_isActive = false;
	}
}

void AudioManager::PlayFadeInBgm(XACT_WAVEBANK_SOUNDS bgmName, float fadeTime)
{
	// �t�F�[�h���̓X�L�b�v
	if (m_isActive) return;

	// ����BGM���~����
	if (m_currentBGM)
	{
		m_currentBGM->Stop(true);
	}

	// �V����BGM���Đ�����
	m_bgms.at(bgmName)->Play(true);
	// �V����BGM������BGM�Ƃ���
	m_currentBGM = m_bgms.at(bgmName).get();
	// �V����BGM�̉��ʂ�0�ɂ���
	m_currentBGM->SetVolume(0.0f);

	// �t�F�[�h���A�N�e�B�u�ɂ���
	m_isActive = true;
}

void AudioManager::StopFadeOutBgm( float fadeTime)
{
	// ���ʂ����݂̉��ʁ`0�Ƀt�F�[�h����
	fadeFuture = std::async(std::launch::async, [this, fadeTime]()
	{
		// �t�F�[�h���̓X�L�b�v
		if (m_isActive) return;

		// �t�F�[�h���ɂ���
		m_isActive = true;
		// ���݂̐��l
		float currentValue = m_bgmVolume;

		while (currentValue > 0)
		{
			if (!m_isActive) break;

			// 1�ɒB����܂ł̑�����
			const float increment = m_bgmVolume / (fadeTime / float(m_stepTimer.GetElapsedSeconds()));

			currentValue -= increment;

			// ���ʐݒ�
			m_currentBGM->SetVolume(currentValue);

			if (currentValue < 0) {
				// ����
				m_currentBGM->SetVolume(0.0f);
				// �����~�߂�
				m_currentBGM->Stop(true);
				// nullptr�ɂ���
				m_currentBGM = nullptr;
			}

			// �t���[���ҋ@ (16ms �� 60FPS����)
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		}

		// �t�F�[�h���ɂ���
		m_isActive = false;

	});
}

// SE���Đ�������
void AudioManager::PlaySE()
{
	m_soundEffectInstanceSE->Play();
	m_isSE = true;
}

// �}�X�^�[���ʂ�ݒ�
void AudioManager::SetMasterVolume(const float& volume)
{
	// �}�X�^�[���ʂ�ݒ�
	m_masterVolume = volume;
	// �I�[�f�B�I�G���W���ɉ��ʐݒ�
	m_audioEngine->SetMasterVolume(volume);
}

// SE���ʂ�ݒ�
void AudioManager::SetSeVolume(const float& volume)
{
	// SE���ʂ�ݒ�
	m_seVolume = volume;
	// �T�E���h�G�t�F�N�g�ɉ��ʂ�ݒ肷��

}

// BGM���ʂ�ݒ�
void AudioManager::SetBgmVolume(const float& volume)
{
	// BGM���ʂ�ݒ�
	m_bgmVolume = volume;
	// �T�E���h�G�t�F�N�g�ɉ��ʂ�ݒ肷��

}