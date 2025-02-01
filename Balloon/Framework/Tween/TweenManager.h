#pragma once
#include <memory>
#include "Framework/Tween/Tween.h"
#include "Framework/StepTimer.h"

class Tween;
class CommonResources;

class TweenManager {

private:

	static const int INITIAL_TWEEN_COUNT;

private:
	//	コンストラクタ
	TweenManager();
	// デストラクタ
	~TweenManager();
public:
	TweenManager(const TweenManager&) = delete;             // コピー禁止
	TweenManager& operator=(const TweenManager&) = delete;  // コピー代入禁止
	TweenManager(const TweenManager&&) = delete;            // ムーブ禁止
	TweenManager& operator=(const TweenManager&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static TweenManager* GetInstance()
	{
		static TweenManager instance;
		return &instance;
	}

public:
    // 更新処理
    void Update();
	// 非アクティブのTweenを取得する
	Tween* GetTween();

private:
	// 共有リソース
	CommonResources* m_commonResources;
    // tweenを格納
    std::vector<std::unique_ptr<Tween>> tweens;
};