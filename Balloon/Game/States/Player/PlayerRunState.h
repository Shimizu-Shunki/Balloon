// ============================================
// 
// ファイル名: PlayerRunState.h
// 概要: PlayerRunState.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IState.h"

class Transform;
class PhysicsBody;


class PlayerRunState : public IState
{
public:
    // コンストラクタ
    PlayerRunState(Transform* transform , PhysicsBody* physicsBody);
    // デストラクタ
    ~PlayerRunState() = default;

    // 初期化処理
    void PreUpdate() override;
    // 更新処理
    void Update(const float& deltaTime) override;
    // 終了処理
    void PostUpdate() override;

private:
    // 移動処理
    DirectX::SimpleMath::Vector3 GetMovementDirection();

private:

    // プレイヤーTransform
    Transform* m_transform;
    // プレイヤー物理挙動
    PhysicsBody* m_physicsBody;
};