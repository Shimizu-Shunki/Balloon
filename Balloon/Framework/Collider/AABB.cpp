// ============================================
// 
// ファイル名: AABB.cpp
// 概要: AABBの判定処理
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Framework/Collider/AABB.h"
#include "Game/PhysicsBody/PhysicsBody.h"

/// <summary>
/// コンストラクタ
/// </summary>
AABB::AABB()
{

}

/// <summary>
/// 判定処理
/// </summary>
/// <param name="box1">ボックス1</param>
/// <param name="box2">ボックス2</param>
/// <returns>衝突しているか</returns>
const bool AABB::Intersects(const DirectX::BoundingBox& box1, const DirectX::BoundingBox& box2)
{
	return box1.Intersects(box2);
}

/// <summary>
/// 押し戻し処理
/// </summary>
/// <param name="object1">オブジェクト1</param>
/// <param name="collider1">当たり判定1</param>
/// <param name="physicsBody1">物理挙動1</param>
/// <param name="object2">オブジェクト2</param>
/// <param name="collider2">当たり判定2</param>
/// <param name="physicsBody2">物理挙動2</param>
/// <returns></returns>
const void AABB::PushBack(IObject* object1, ICollider* collider1, PhysicsBody* physicsBody1,
    IObject* object2, ICollider* collider2, PhysicsBody* physicsBody2)
{
    // オブジェクト1とオブジェクト2のバウンディングボックスを取得
    DirectX::BoundingBox collision1;
    DirectX::BoundingBox collision2;

    collision1.Center = collider1->GetTransform()->GetWorldPosition();
    collision2.Center = collider2->GetTransform()->GetWorldPosition();

    collision1.Extents = collider1->GetTransform()->GetWorldScale() / 2.0f;
    collision2.Extents = collider2->GetTransform()->GetWorldScale() / 2.0f;


    // 中心座標を取得
    const auto& center1 = collision1.Center;
    const auto& center2 = collision2.Center;

    // 各軸でのオーバーラップ量を計算
    float xOverlap = (collision1.Extents.x + collision2.Extents.x) - std::abs(center1.x - center2.x);
    float yOverlap = (collision1.Extents.y + collision2.Extents.y) - std::abs(center1.y - center2.y);
    float zOverlap = (collision1.Extents.z + collision2.Extents.z) - std::abs(center1.z - center2.z);

    // 重なりがない場合は押し戻し処理を行わない
    if (xOverlap <= 0 || yOverlap <= 0 || zOverlap <= 0)
        return;

    // 最小オーバーラップを計算
    float minOverlap = std::min({ xOverlap, yOverlap, zOverlap });

    // **オブジェクト1がオブジェクト2のTopに接触しているか判定**
    bool isTopCollision = (minOverlap == yOverlap) && (center1.y > center2.y);

    // 押し戻し方向を決定
    DirectX::SimpleMath::Vector3 pushback = DirectX::SimpleMath::Vector3::Zero;
    if (minOverlap == xOverlap)
    {
        pushback.x = (center1.x > center2.x ? xOverlap : -xOverlap);
    }
    else if (minOverlap == yOverlap)
    {
        pushback.y = (center1.y > center2.y ? yOverlap : -yOverlap);
    }
    else if (minOverlap == zOverlap)
    {
        pushback.z = (center1.z > center2.z ? zOverlap : -zOverlap);
    }

    // オブジェクトの質量を取得
    float mass1 = 1.0f;
    float mass2 = 1.0f;

    bool kinematic1 = false;
    bool kinematic2 = false;

    // 両方リジットボディがない場合押し戻し処理をしない
    if (physicsBody1 == nullptr && physicsBody2 == nullptr)
    {
        return;
    }

    // 質量とキネマティックを取得
    if (physicsBody1 != nullptr)
    {
        mass1      = physicsBody1->GetMass();
        kinematic1 = physicsBody1->GetIsKinematic();
    }
    if (physicsBody2 != nullptr)
    {
        mass2      = physicsBody2->GetMass();
        kinematic2 = physicsBody2->GetIsKinematic();
    }
       
    float totalMass = mass1 + mass2;

    DirectX::SimpleMath::Vector3 pushback1;
    DirectX::SimpleMath::Vector3 pushback2;

    // 押し戻しを分配する
    if (!kinematic1 && !kinematic2 && physicsBody1 != nullptr && physicsBody2 != nullptr)
    {
        // 押し戻しを質量比で分配
        pushback1 = pushback * (mass2 / totalMass);
        pushback2 = pushback * -(mass1 / totalMass);
    }
    else if (!kinematic1 && kinematic2)
    {
        // 押し戻しを質量比で分配
        pushback1 = pushback;
        pushback2 = DirectX::SimpleMath::Vector3::Zero;
    }
    DirectX::SimpleMath::Vector3 as = object1->GetTransform()->GetLocalPosition();
    // 親のTransformのローカル座標の位置を更新
    object1->GetTransform()->SetLocalPosition(object1->GetTransform()->GetLocalPosition() + pushback1);

    object2->GetTransform()->SetLocalPosition(object2->GetTransform()->GetLocalPosition() + pushback2);


    // 重力設定
    if (isTopCollision && physicsBody1 != nullptr)
    {
        // Yの速度を0にする
        physicsBody1->SetVelocity({
            physicsBody1->GetVelocity().x,
            0.0f,
            physicsBody1->GetVelocity().z
         });

        // 重力を無効化
        physicsBody1->SetUseGravity(false);
    }
    else if(!isTopCollision && physicsBody1 != nullptr)
    {
        // 重力を有効化
        physicsBody1->SetUseGravity(true);
    }

    DirectX::SimpleMath::Vector3 ss = object1->GetTransform()->GetLocalPosition();

    // Transformの更新を再度行う
    object1->GetTransform()->Update();
    object2->GetTransform()->Update();
}


/// <summary>
/// 上下左右前後の判定処理
/// </summary>
/// <param name="box1">当たり判定1</param>
/// <param name="box2">当たり判定2</param>
/// <returns>判定結果</returns>
const int AABB::DetermineCollisionDirection(const DirectX::BoundingBox& box1, const DirectX::BoundingBox& box2)
{
    int direction = CollisionDirection::NONE;

    // 中心座標とサイズを取得
    DirectX::XMFLOAT3 center1 = box1.Center;
    DirectX::XMFLOAT3 extents1 = box1.Extents;

    DirectX::XMFLOAT3 center2 = box2.Center;
    DirectX::XMFLOAT3 extents2 = box2.Extents;

    // 中心座標の差分
    float xDiff = center2.x - center1.x;
    float yDiff = center2.y - center1.y;
    float zDiff = center2.z - center1.z;

    // 横方向の判定（左右）
    if (std::abs(xDiff) < (extents1.x + extents2.x)) {
        if (xDiff > 0) {
            direction |= CollisionDirection::RIGHT;  // 右側に衝突
        }
        else if (xDiff < 0) {
            direction |= CollisionDirection::LEFT;   // 左側に衝突
        }
    }

    // 縦方向の判定（上下）
    if (std::abs(yDiff) < (extents1.y + extents2.y)) {
        if (yDiff > 0) {
            direction |= CollisionDirection::UP;     // 上側に衝突
        }
        else if (yDiff < 0) {
            direction |= CollisionDirection::DOWN;   // 下側に衝突
        }
    }

    // 奥行き方向の判定（前後）
    if (std::abs(zDiff) < (extents1.z + extents2.z)) {
        if (zDiff > 0) {
            direction |= CollisionDirection::FRONT;  // 前側に衝突
        }
        else if (zDiff < 0) {
            direction |= CollisionDirection::BACK;   // 後側に衝突
        }
    }

    return direction;
}