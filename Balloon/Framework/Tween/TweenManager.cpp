#include "Framework/pch.h"
#include "Framework/Tween/TweenManager.h"
#include "Framework/CommonResources.h"

const int TweenManager::INITIAL_TWEEN_COUNT = 10;

// コンストラクタ
TweenManager::TweenManager()
{
    // 共有リソースを取得する
    m_commonResources = CommonResources::GetInstance();
    
    // 初期として10個のTweenを用意しておく
    for (int i = 0; i < INITIAL_TWEEN_COUNT; i++)
    {
        tweens.push_back(std::make_unique<Tween>());
    }
}

// デストラクタ
TweenManager::~TweenManager()
{

}

/// <summary>
/// Tweenを取得する
/// </summary>
Tween* TweenManager::GetTween()
{
    for (const auto& tween : tweens)
    {
        // 非アクティブな状態のTweenを渡す
        if (!tween->GetIsActive())
        {
            return tween.get();
        }
    }
    // もし全て起動中ならば新にTweenを作成する
    tweens.push_back(std::make_unique<Tween>());
    // 起動していないTweenを返す
    return tweens.back().get();
}

/// <summary>
/// 更新処理
/// </summary>
void TweenManager::Update()
{
    // 経過時間（秒単位）を取得
    const float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

    // Tweenの更新処理
    for (const auto& tween : tweens)
    {
        // Tweenが進行中の物のみ更新処理を行う
        if (tween->GetIsActive())
        {
            tween->Update(elapsedTime);
        }
    }
}