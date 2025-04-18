// ============================================
// 
// ファイル名: AudioManager.cpp
// 概要: 音全般を管理するクラス（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================

#include "pch.h"
#include "Framework/AudioManager.h"
#include "Framework/Sounds.h"
#include <Audio.h>

/// <summary>
/// コンストラクタ
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
/// デストラクタ
/// </summary>
AudioManager::~AudioManager()
{
	m_isActive = false;

	// オーディオエンジンの後始末
	if (m_audioEngine)
	{
		m_audioEngine->Suspend();
	}
}

/// <summary>
/// 初期化処理
/// </summary>
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
	m_bgmVolume    = 0.5f;

	// オーディオエンジンを作成する
	m_audioEngine = std::make_unique<DirectX::AudioEngine>(eflags);
	// マスター音量の初期化
	m_audioEngine->SetMasterVolume(m_masterVolume);

	// サウンドバンクを作成する
	m_waveBank = std::make_unique<DirectX::WaveBank>
		(m_audioEngine.get(), L"Resources/Sounds/BGM.xwb");

	// BGMをマップに登録する
	for (int i = 0; i < XACT_WAVEBANK_SOUNDS_ENTRY_COUNT; i++)
	{
		m_bgms.insert(BgmMap::value_type((XACT_WAVEBANK_SOUNDS)i, m_waveBank->CreateInstance((XACT_WAVEBANK_SOUNDS)i)));
	}

	// サウンドバンクを作成する
	m_waveBankSe = std::make_unique<DirectX::WaveBank>
		(m_audioEngine.get(), L"Resources/Sounds/SE.xwb");

	// SEをマップに登録する
	for (int i = 0; i < XACT_WAVEBANK_SOUNDS_ENTRY_COUNT_SE; i++)
	{
		m_ses.insert(SeMap::value_type((XACT_WAVEBANK_SOUNDS_SE)i, m_waveBankSe->CreateInstance((XACT_WAVEBANK_SOUNDS_SE)i)));
	}

	// インスタンスの初期化
	m_currentBGM = nullptr;
	m_currentSE = nullptr;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="timer">経過時間</param>
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

	// SEが再生されたら数秒で停止する
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

	// BGMのフェード処理
	if (!m_isActive) return;

	// 経過時間を更新
	m_fadeElapsedTime += (float)timer.GetElapsedSeconds();

	// 線形補間を使用して音量を更新
	float t = m_fadeElapsedTime / m_fadeTime; // 0.0f〜1.0f の範囲
	t = std::min(t, 1.0f); // tが1を超えないように制限
	
	// 現在の音量を更新
	m_currentValue = m_startValueme + t * (m_endValueme - m_startValueme);
	// 音量設定
	m_currentBGM->SetVolume(m_currentValue);
	
	// フェードが終了したら
	if (t >= 1.0f) {
		m_currentValue = m_endValueme;
		// 最終音量を設定
		m_currentBGM->SetVolume(m_currentValue);

		if(m_currentValue <= 0.0f)
		// 音量が0になった時はBGMを停止する
		m_currentBGM->Stop(true);

		// フェードを非アクティブ
		m_isActive = false;
	}
}

/// <summary>
/// フェードインしながらBGMを再生
/// </summary>
/// <param name="bgmName">BGM</param>
/// <param name="fadeTime">フェード時間</param>
void AudioManager::PlayFadeInBgm(XACT_WAVEBANK_SOUNDS bgmName, float fadeTime)
{
	// フェード中はスキップ
	if (m_isActive) return;

	// 今のBGMを停止する
	if (m_currentBGM) m_currentBGM->Stop(true);

	// 新しいBGMを再生する
	m_bgms.at(bgmName)->Play(true);
	// 新しいBGMを今のBGMとする
	m_currentBGM = m_bgms.at(bgmName).get();
	// 新しいBGMの音量を0にする
	m_currentBGM->SetVolume(0.0f);

	// フェード時間を設定
	m_fadeTime = fadeTime;
	// スタート音量設定
	m_startValueme = 0.0f;
	// 終了音量設定
	m_endValueme = m_bgmVolume;
	// 現在の音量を初期化
	m_currentValue = 0.0f;
	m_fadeElapsedTime = 0.0f;

	// フェードをアクティブにする
	m_isActive = true;
}

/// <summary>
/// フェードアウトしながらBGMを停止する
/// </summary>
/// <param name="fadeTime">フェード時間</param>
void AudioManager::StopFadeOutBgm( float fadeTime)
{
	// フェード中はスキップ
	if (m_isActive) return;

	// フェード時間を設定
	m_fadeTime = fadeTime;
	// スタート音量設定
	m_startValueme = m_bgmVolume;
	// 終了音量設定
	m_endValueme = 0.0f;
	// 現在の音量を初期化
	m_currentValue = 0.0f;
	m_fadeElapsedTime = 0.0f;

	// フェードをアクティブにする
	m_isActive = true;
}

/// <summary>
/// SEを再生する
/// </summary>
void AudioManager::PlaySE(XACT_WAVEBANK_SOUNDS_SE bgmName)
{
	// 今のSEを停止
	if (m_currentSE)
	{
		m_currentSE->Stop(true);
		m_seTimer = 0.0f;
		m_stopSeTime = 2.0f;
	}

	// 新しいBGMを再生する
	m_ses.at(bgmName)->Play(true);
	// 新しいBGMを今のBGMとする
	m_currentSE = m_ses.at(bgmName).get();
	// 新しいBGMの音量を0にする
	m_currentSE->SetVolume(m_seVolume);

	m_currentSE->Play();
	m_isSE = true;
}

/// <summary>
/// SEを再生する
/// </summary>
void AudioManager::PlaySE(XACT_WAVEBANK_SOUNDS_SE bgmName, float time)
{
	// 今のSEを停止
	if (m_currentSE)
	{
		m_currentSE->Stop(true);
		m_seTimer = 0.0f;
		m_isSE = false;
	}

	// 新しいBGMを再生する
	//m_ses.at(bgmName)->Play(true);
	// 新しいBGMを今のBGMとする
	m_currentSE = m_ses.at(bgmName).get();
	// 新しいBGMの音量を0にする
	m_currentSE->SetVolume(m_seVolume);

	m_stopSeTime = time;

	m_currentSE->Play();
	m_isSE = true;
}

/// <summary>
/// SEをループ再生
/// </summary>
/// <param name="bgmName"></param>
void AudioManager::PlayLoopSE(XACT_WAVEBANK_SOUNDS_SE bgmName)
{
	// 今のSEを停止
	if (m_currentSE)
	{
		m_currentSE->Stop(true);
		m_seTimer = 0.0f;
		m_stopSeTime = 2.0f;
	}

	// 新しいBGMを再生する
	m_ses.at(bgmName)->Play(true);
	// 新しいBGMを今のBGMとする
	m_currentSE = m_ses.at(bgmName).get();
	// 新しいBGMの音量を0にする
	m_currentSE->SetVolume(m_seVolume);

	m_currentSE->IsLooped();
	m_currentSE->Play();
}

/// <summary>
/// ループ再生を停止する
/// </summary>
void AudioManager::StopSE()
{
	m_currentSE->IsLooped();
	m_currentSE->Stop();
}

/// <summary>
/// マスター音量を設定
/// </summary>
/// <param name="volume">音量</param>
void AudioManager::SetMasterVolume(const float& volume)
{
	// マスター音量を設定
	m_masterVolume = volume;
	// オーディオエンジンに音量設定
	m_audioEngine->SetMasterVolume(volume);
}

/// <summary>
/// SE音量を設定
/// </summary>
/// <param name="volume">音量</param>
void AudioManager::SetSeVolume(const float& volume)
{
	// SE音量を設定
	m_seVolume = volume;
	// サウンドエフェクトに音量を設定する
	m_currentSE->SetVolume(m_seVolume);
}

/// <summary>
/// BGM音量を設定
/// </summary>
/// <param name="volume">音量</param>
void AudioManager::SetBgmVolume(const float& volume)
{
	// BGM音量を設定
	m_bgmVolume = volume;
	// サウンドエフェクトに音量を設定する
	m_currentBGM->SetVolume(m_bgmVolume);
}