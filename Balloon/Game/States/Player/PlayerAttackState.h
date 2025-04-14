// ============================================
// 
// ファイル名: PlayerAttackState.h
// 概要: PlayerAttackState.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class Transform;
class PhysicsBody;
class Player;

class PlayerAttackState : public IState
{
public:
    // コンストラクタ
    PlayerAttackState(Player* player);
    // デストラクタ
    ~PlayerAttackState() = default;

    // 初期化処理
    void PreUpdate() override;
    // 更新処理
    void Update(const float& deltaTime) override;
    // 終了処理
    void PostUpdate() override;

private:

    // プレイヤーオブジェクト
    Player* m_player;

    // アタック時間
    float m_moveingTime;
    // 経過時間
    float m_elapsedTime;
};