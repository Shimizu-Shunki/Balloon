// ============================================
// 
// ファイル名: PlayerIdleState.h
// 概要: PlayerIdleState.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class Transform;

class PlayerIdleState : public IState
{
public:
    // コンストラクタ
    PlayerIdleState();
    // デストラクタ
    ~PlayerIdleState() = default;

    // 初期化処理
    void PreUpdate() override;
    // 更新処理
    void Update(const float& deltaTime) override;
    // 終了処理
    void PostUpdate() override;

private:

    // プレイヤーTransform
    Transform* m_transform;
};