#include "pch.h"
#include "Framework/AudioManager.h"
#include "Framework/Sounds.h"
#include <Audio.h>
#include <chrono>

std::unique_ptr<AudioManager> AudioManager::m_audioManager = nullptr;

// オーディオマネージャーのインスタンスを作成する
AudioManager* const AudioManager::GetInstance()
{
	if (m_audioManager == nullptr)
	{
		// オーディオマネージャーのインスタンスを生成する
		m_audioManager.reset(new AudioManager());
	}
	// オーディオマネージャーのインスタンスを返す
	return m_audioManager.get();
}

// コンストラクタ
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

// デストラクタ
AudioManager::~AudioManager()
{
	m_isActive = false;

	// オーディオエンジンの後始末
	if (m_audioEngine)
	{
		m_audioEngine->Suspend();
	}
}

// 初期化処理
void AudioManager::Initialize()
{
	// オーディオエンジンのフラグ
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AUDIO_ENGINE_FLAGS::AudioEngine_Default;
#ifdef _DEBUG
	eflags |= DirectX::AUDIO_ENGINE_FLAGS::AudioEngine_Debug;
#endif

	// 音量をすべて1に初期化
	m_masterVolume = 1.0f;
	m_seVolume     = 1.0f;
	m_bgmVolume    = 1.0f;

	// オーディオエンジンを作成する
	m_audioEngine = std::make_unique<DirectX::AudioEngine>(eflags);
	// マスター音量の初期化
	m_audioEngine->SetMasterVolume(m_masterVolume);

	// サウンドバンクを作成する
	m_waveBank = std::make_unique<DirectX::WaveBank>
		(m_audioEngine.get(), L"Resources/Sounds/BGM.xwb");

	// BGMをマップに登録する
	m_bgms.insert(BgmMap::value_type(XACT_WAVEBANK_SOUNDS_TITLESCENE, m_waveBank->CreateInstance(XACT_WAVEBANK_SOUNDS_TITLESCENE)));
	m_bgms.insert(BgmMap::value_type(XACT_WAVEBANK_SOUNDS_SELECTSCENE, m_waveBank->CreateInstance(XACT_WAVEBANK_SOUNDS_SELECTSCENE)));
	m_bgms.insert(BgmMap::value_type(XACT_WAVEBANK_SOUNDS_PLAYSCENE, m_waveBank->CreateInstance(XACT_WAVEBANK_SOUNDS_PLAYSCENE)));
	m_bgms.insert(BgmMap::value_type(XACT_WAVEBANK_SOUNDS_GAMECLEARSCENE, m_waveBank->CreateInstance(XACT_WAVEBANK_SOUNDS_GAMECLEARSCENE)));
	m_bgms.insert(BgmMap::value_type(XACT_WAVEBANK_SOUNDS_GAMEOVERSCENE, m_waveBank->CreateInstance(XACT_WAVEBANK_SOUNDS_GAMEOVERSCENE)));

	// インスタンスの初期化
	m_currentBGM = nullptr;
}

void AudioManager::Update(DX::StepTimer const& timer)
{
	// オーディオエンジンを更新する
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

	// BGMのフェード処理
	if (!m_isActive) return;

	// 1に達するまでの増加量
	const float increment = m_bgmVolume / (m_fadeTime / float(m_stepTimer.GetElapsedSeconds()));


	m_currentValue =  + increment * (end - start);

	// 現在のボリュームを更新
	m_currentValue += increment;

	// 音量設定
	m_currentBGM->SetVolume(m_currentValue);
	


	// フェードが終了したら
	if (m_currentValue > m_bgmVolume) {
		m_currentValue = m_bgmVolume;
		// 最終音量を設定
		m_currentBGM->SetVolume(m_bgmVolume);
		// 現在の音量を初期化
		m_currentValue = 0.0f;
		// フェード時間を初期化
		m_fadeTime = 0.0f;
		// フェードを非アクティブ
		m_isActive = false;
	}
}

void AudioManager::PlayFadeInBgm(XACT_WAVEBANK_SOUNDS bgmName, float fadeTime)
{
	// フェード中はスキップ
	if (m_isActive) return;

	// 今のBGMを停止する
	if (m_currentBGM)
	{
		m_currentBGM->Stop(true);
	}

	// 新しいBGMを再生する
	m_bgms.at(bgmName)->Play(true);
	// 新しいBGMを今のBGMとする
	m_currentBGM = m_bgms.at(bgmName).get();
	// 新しいBGMの音量を0にする
	m_currentBGM->SetVolume(0.0f);

	// フェードをアクティブにする
	m_isActive = true;
}

void AudioManager::StopFadeOutBgm( float fadeTime)
{
	// 音量を現在の音量～0にフェードする
	fadeFuture = std::async(std::launch::async, [this, fadeTime]()
	{
		// フェード中はスキップ
		if (m_isActive) return;

		// フェード中にする
		m_isActive = true;
		// 現在の数値
		float currentValue = m_bgmVolume;

		while (currentValue > 0)
		{
			if (!m_isActive) break;

			// 1に達するまでの増加量
			const float increment = m_bgmVolume / (fadeTime / float(m_stepTimer.GetElapsedSeconds()));

			currentValue -= increment;

			// 音量設定
			m_currentBGM->SetVolume(currentValue);

			if (currentValue < 0) {
				// 音量
				m_currentBGM->SetVolume(0.0f);
				// 音を止める
				m_currentBGM->Stop(true);
				// nullptrにする
				m_currentBGM = nullptr;
			}

			// フレーム待機 (16ms → 60FPS相当)
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		}

		// フェード中にする
		m_isActive = false;

	});
}

// SEを再生させる
void AudioManager::PlaySE()
{
	m_soundEffectInstanceSE->Play();
	m_isSE = true;
}

// マスター音量を設定
void AudioManager::SetMasterVolume(const float& volume)
{
	// マスター音量を設定
	m_masterVolume = volume;
	// オーディオエンジンに音量設定
	m_audioEngine->SetMasterVolume(volume);
}

// SE音量を設定
void AudioManager::SetSeVolume(const float& volume)
{
	// SE音量を設定
	m_seVolume = volume;
	// サウンドエフェクトに音量を設定する

}

// BGM音量を設定
void AudioManager::SetBgmVolume(const float& volume)
{
	// BGM音量を設定
	m_bgmVolume = volume;
	// サウンドエフェクトに音量を設定する

}