#include "pch.h"
#include "Game/SteeringBehavior/SeekBehavior.h"
#include "Game/Object/Object.h"


SeekBehavior::SeekBehavior(Object* object, Object* target)
{
    m_object = object;
    m_target = target;
}


DirectX::SimpleMath::Vector3 SeekBehavior::Calculate()
{

    // 相手の座標
    const DirectX::SimpleMath::Vector3 position = m_target->GetTransform()->GetLocalPosition();
    // 相手の速度
    const DirectX::SimpleMath::Vector3 velocity = m_target->GetVelocity();

    // 相手の向きを計算
    const DirectX::SimpleMath::Vector3 toTargetPosition =
        m_object->GetTransform()->GetLocalPosition() - m_target->GetTransform()->GetLocalPosition();


    // 相手の速度の一秒後の位置を加算する
    float distance = toTargetPosition.Length();
    float speed = m_object->GetVelocity().Length() + 0.01f;

    // 先読み時間を計算
    float lookAheadTime = distance / speed;

    // 予測位置を計算
    DirectX::SimpleMath::Vector3 futurePos = position + velocity * lookAheadTime;

    DirectX::SimpleMath::Vector3 desired = futurePos - m_object->GetTransform()->GetLocalPosition();
    desired.y = 0.0f;
    desired.Normalize();
    desired *= 2.0f;


    return desired;
}