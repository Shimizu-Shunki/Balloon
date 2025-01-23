#pragma once
#include <future>
#include "Sounds.h"


class AudioManager
{
	// BGMの再生
	// SEの再生

	// BGMの再生　フェードアウト
	// BGMの停止　フェードイン

public :

	// デストラクタ
	~AudioManager();

	// InputManagerクラスのインスタンスを取得する
	static AudioManager* const GetInstance();
	// マスター音量を設定する
	void SetMasterVolume(const float& volume);
	// SEの音量を設定する
	void SetSeVolume(const float& volume);
	// BGMの音量を設定する
	void SetBgmVolume(const float& volume);


public:
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(DX::StepTimer const& timer);

	// プレイBGM
	void PlayFadeInBgm(XACT_WAVEBANK_SOUNDS bgmName, float fadeTime = 1.0f);
	// ストップBGM
	void StopFadeOutBgm(float fadeTime = 1.0f);

	// SEを再生
	void PlaySE();

private:
	// コンストラクタ
	AudioManager();

	


private:
	// タイマー
	DX::StepTimer m_stepTimer;

	using BgmMap = std::unordered_map<XACT_WAVEBANK_SOUNDS, std::unique_ptr<DirectX::SoundEffectInstance>>;

	// AudioManagerクラスのインスタンスへのポインタ
	static std::unique_ptr<AudioManager> m_audioManager;

	// オーディオエンジン
	std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
	// BGMのバンク
	std::unique_ptr<DirectX::WaveBank> m_waveBank;
	// BGMの格納
	BgmMap m_bgms;
	// BGMのインスタンス
	DirectX::SoundEffectInstance* m_currentBGM;

	// フェードフラグ
	bool m_isActive;
	// SEフラグ
	bool m_isSE;
	// タイム
	float m_timer;
	// フェードタイム
	float m_fadeTime;
	// 現在の音量
	float m_currentValue;

	std::unique_ptr<DirectX::SoundEffect> m_soundEffectBGM;
	

	std::unique_ptr<DirectX::SoundEffect> m_soundEffectSE;
	std::unique_ptr<DirectX::SoundEffectInstance> m_soundEffectInstanceSE;
	// マスター音量
	float m_masterVolume;
	// SEの音量
	float m_seVolume;
	// BGMの音量
	float m_bgmVolume;

	// 非同期処理の管理
	std::future<void> fadeFuture; 
};