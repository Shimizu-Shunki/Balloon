// ============================================
// 
// �t�@�C����: AudioManager.cpp
// �T�v: ���S�ʂ��Ǘ�����N���X�i�V���O���g���j
// 
// ����� : �����x��
// 
// ============================================

#include "Framework/pch.h"
#include "Framework/AudioManager.h"
#include "Framework/Sounds.h"
#include <Audio.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
AudioManager::AudioManager()
	:
	m_audioEngine{},
	m_waveBank{},
	m_bgms{},
	m_currentBGM{},
	m_waveBankSe{},
	m_ses{},
	m_currentSE{},
	m_masterVolume{},
	m_seVolume{},
	m_bgmVolume{},
	m_fadeTime{},
	m_currentValue{},
	m_fadeElapsedTime{},
	m_startValueme{},
	m_endValueme{}
{
	m_isActive = false;
	m_isSE = false;
	m_seTimer = 0.0f;
	m_stopSeTime = 2.0f;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
AudioManager::~AudioManager()
{
	m_isActive = false;

	// �I�[�f�B�I�G���W���̌�n��
	if (m_audioEngine)
	{
		m_audioEngine->Suspend();
	}
}

/// <summary>
/// ����������
/// </summary>
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
	m_bgmVolume    = 0.5f;

	// �I�[�f�B�I�G���W�����쐬����
	m_audioEngine = std::make_unique<DirectX::AudioEngine>(eflags);
	// �}�X�^�[���ʂ̏�����
	m_audioEngine->SetMasterVolume(m_masterVolume);

	// �T�E���h�o���N���쐬����
	m_waveBank = std::make_unique<DirectX::WaveBank>
		(m_audioEngine.get(), L"Resources/Sounds/BGM.xwb");

	// BGM���}�b�v�ɓo�^����
	for (int i = 0; i < XACT_WAVEBANK_SOUNDS_ENTRY_COUNT; i++)
	{
		m_bgms.insert(BgmMap::value_type((XACT_WAVEBANK_SOUNDS)i, m_waveBank->CreateInstance((XACT_WAVEBANK_SOUNDS)i)));
	}

	// �T�E���h�o���N���쐬����
	m_waveBankSe = std::make_unique<DirectX::WaveBank>
		(m_audioEngine.get(), L"Resources/Sounds/SE.xwb");

	// SE���}�b�v�ɓo�^����
	for (int i = 0; i < XACT_WAVEBANK_SOUNDS_ENTRY_COUNT_SE; i++)
	{
		m_ses.insert(SeMap::value_type((XACT_WAVEBANK_SOUNDS_SE)i, m_waveBankSe->CreateInstance((XACT_WAVEBANK_SOUNDS_SE)i)));
	}

	// �C���X�^���X�̏�����
	m_currentBGM = nullptr;
	m_currentSE = nullptr;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="timer">�o�ߎ���</param>
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

	// SE���Đ����ꂽ�琔�b�Œ�~����
	if (m_isSE)
	{
		m_seTimer += float(timer.GetElapsedSeconds());
		if (m_seTimer >= m_stopSeTime)
		{
			m_seTimer = 0.0f;
			m_stopSeTime = 2.0f;
			m_currentSE->Stop();
			m_isSE = false;
		}
	}

	// BGM�̃t�F�[�h����
	if (!m_isActive) return;

	// �o�ߎ��Ԃ��X�V
	m_fadeElapsedTime += (float)timer.GetElapsedSeconds();

	// ���`��Ԃ��g�p���ĉ��ʂ��X�V
	float t = m_fadeElapsedTime / m_fadeTime; // 0.0f�`1.0f �͈̔�
	t = std::min(t, 1.0f); // t��1�𒴂��Ȃ��悤�ɐ���
	
	// ���݂̉��ʂ��X�V
	m_currentValue = m_startValueme + t * (m_endValueme - m_startValueme);
	// ���ʐݒ�
	m_currentBGM->SetVolume(m_currentValue);
	
	// �t�F�[�h���I��������
	if (t >= 1.0f) {
		m_currentValue = m_endValueme;
		// �ŏI���ʂ�ݒ�
		m_currentBGM->SetVolume(m_currentValue);

		if(m_currentValue <= 0.0f)
		// ���ʂ�0�ɂȂ�������BGM���~����
		m_currentBGM->Stop(true);

		// �t�F�[�h���A�N�e�B�u
		m_isActive = false;
	}
}

/// <summary>
/// �t�F�[�h�C�����Ȃ���BGM���Đ�
/// </summary>
/// <param name="bgmName">BGM</param>
/// <param name="fadeTime">�t�F�[�h����</param>
void AudioManager::PlayFadeInBgm(XACT_WAVEBANK_SOUNDS bgmName, float fadeTime)
{
	// �t�F�[�h���̓X�L�b�v
	if (m_isActive) return;

	// ����BGM���~����
	if (m_currentBGM) m_currentBGM->Stop(true);

	// �V����BGM���Đ�����
	m_bgms.at(bgmName)->Play(true);
	// �V����BGM������BGM�Ƃ���
	m_currentBGM = m_bgms.at(bgmName).get();
	// �V����BGM�̉��ʂ�0�ɂ���
	m_currentBGM->SetVolume(0.0f);

	// �t�F�[�h���Ԃ�ݒ�
	m_fadeTime = fadeTime;
	// �X�^�[�g���ʐݒ�
	m_startValueme = 0.0f;
	// �I�����ʐݒ�
	m_endValueme = m_bgmVolume;
	// ���݂̉��ʂ�������
	m_currentValue = 0.0f;
	m_fadeElapsedTime = 0.0f;

	// �t�F�[�h���A�N�e�B�u�ɂ���
	m_isActive = true;
}

/// <summary>
/// �t�F�[�h�A�E�g���Ȃ���BGM���~����
/// </summary>
/// <param name="fadeTime">�t�F�[�h����</param>
void AudioManager::StopFadeOutBgm( float fadeTime)
{
	// �t�F�[�h���̓X�L�b�v
	if (m_isActive) return;

	// �t�F�[�h���Ԃ�ݒ�
	m_fadeTime = fadeTime;
	// �X�^�[�g���ʐݒ�
	m_startValueme = m_bgmVolume;
	// �I�����ʐݒ�
	m_endValueme = 0.0f;
	// ���݂̉��ʂ�������
	m_currentValue = 0.0f;
	m_fadeElapsedTime = 0.0f;

	// �t�F�[�h���A�N�e�B�u�ɂ���
	m_isActive = true;
}

/// <summary>
/// SE���Đ�����
/// </summary>
void AudioManager::PlaySE(XACT_WAVEBANK_SOUNDS_SE bgmName)
{
	// ����SE���~
	if (m_currentSE)
	{
		m_currentSE->Stop(true);
		m_seTimer = 0.0f;
		m_stopSeTime = 2.0f;
	}

	// �V����BGM���Đ�����
	m_ses.at(bgmName)->Play(true);
	// �V����BGM������BGM�Ƃ���
	m_currentSE = m_ses.at(bgmName).get();
	// �V����BGM�̉��ʂ�0�ɂ���
	m_currentSE->SetVolume(m_seVolume);

	m_currentSE->Play();
	m_isSE = true;
}

/// <summary>
/// SE���Đ�����
/// </summary>
void AudioManager::PlaySE(XACT_WAVEBANK_SOUNDS_SE bgmName, float time)
{
	// ����SE���~
	if (m_currentSE)
	{
		m_currentSE->Stop(true);
		m_seTimer = 0.0f;
		m_isSE = false;
	}

	// �V����BGM���Đ�����
	//m_ses.at(bgmName)->Play(true);
	// �V����BGM������BGM�Ƃ���
	m_currentSE = m_ses.at(bgmName).get();
	// �V����BGM�̉��ʂ�0�ɂ���
	m_currentSE->SetVolume(m_seVolume);

	m_stopSeTime = time;

	m_currentSE->Play();
	m_isSE = true;
}

/// <summary>
/// SE�����[�v�Đ�
/// </summary>
/// <param name="bgmName"></param>
void AudioManager::PlayLoopSE(XACT_WAVEBANK_SOUNDS_SE bgmName)
{
	// ����SE���~
	if (m_currentSE)
	{
		m_currentSE->Stop(true);
		m_seTimer = 0.0f;
		m_stopSeTime = 2.0f;
	}

	// �V����BGM���Đ�����
	m_ses.at(bgmName)->Play(true);
	// �V����BGM������BGM�Ƃ���
	m_currentSE = m_ses.at(bgmName).get();
	// �V����BGM�̉��ʂ�0�ɂ���
	m_currentSE->SetVolume(m_seVolume);

	m_currentSE->IsLooped();
	m_currentSE->Play();
}

/// <summary>
/// ���[�v�Đ����~����
/// </summary>
void AudioManager::StopSE()
{
	m_currentSE->IsLooped();
	m_currentSE->Stop();
}

/// <summary>
/// �}�X�^�[���ʂ�ݒ�
/// </summary>
/// <param name="volume">����</param>
void AudioManager::SetMasterVolume(const float& volume)
{
	// �}�X�^�[���ʂ�ݒ�
	m_masterVolume = volume;
	// �I�[�f�B�I�G���W���ɉ��ʐݒ�
	m_audioEngine->SetMasterVolume(volume);
}

/// <summary>
/// SE���ʂ�ݒ�
/// </summary>
/// <param name="volume">����</param>
void AudioManager::SetSeVolume(const float& volume)
{
	// SE���ʂ�ݒ�
	m_seVolume = volume;
	// �T�E���h�G�t�F�N�g�ɉ��ʂ�ݒ肷��
	m_currentSE->SetVolume(m_seVolume);
}

/// <summary>
/// BGM���ʂ�ݒ�
/// </summary>
/// <param name="volume">����</param>
void AudioManager::SetBgmVolume(const float& volume)
{
	// BGM���ʂ�ݒ�
	m_bgmVolume = volume;
	// �T�E���h�G�t�F�N�g�ɉ��ʂ�ݒ肷��
	m_currentBGM->SetVolume(m_bgmVolume);
}