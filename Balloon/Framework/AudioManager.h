#pragma once
#include <future>
#include "Sounds.h"
#include <Audio.h>



class AudioManager
{
public :
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
	//	コンストラクタ
	AudioManager();
	// デストラクタ
	~AudioManager();
public:
	AudioManager(const AudioManager&) = delete;             // コピー禁止
	AudioManager& operator=(const AudioManager&) = delete;  // コピー代入禁止
	AudioManager(const AudioManager&&) = delete;            // ムーブ禁止
	AudioManager& operator=(const AudioManager&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static AudioManager* GetInstance()
	{
		static AudioManager instance;
		return &instance;
	}

private:
	
	using BgmMap = std::unordered_map<XACT_WAVEBANK_SOUNDS, std::unique_ptr<DirectX::SoundEffectInstance>>;

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
	// SEタイム
	float m_seTimer;
	// フェードタイム
	float m_fadeTime;
	// 現在の音量
	float m_currentValue;

	// フェード中の経過時間
	float m_fadeElapsedTime;
	// スタートボリューム
	float m_startValueme;
	// 終了ボリューム
	float m_endValueme;


	std::unique_ptr<DirectX::SoundEffect> m_soundEffectSE;
	std::unique_ptr<DirectX::SoundEffectInstance> m_soundEffectInstanceSE;
	// マスター音量
	float m_masterVolume;
	// SEの音量
	float m_seVolume;
	// BGMの音量
	float m_bgmVolume;
};