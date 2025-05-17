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

    // ‘ŠŽè‚ÌÀ•W
    const DirectX::SimpleMath::Vector3 position = m_target->GetTransform()->GetLocalPosition();
    // ‘ŠŽè‚Ì‘¬“x
    const DirectX::SimpleMath::Vector3 velocity = m_target->GetVelocity();

    // ‘ŠŽè‚ÌŒü‚«‚ðŒvŽZ
    const DirectX::SimpleMath::Vector3 toTargetPosition =
        m_object->GetTransform()->GetLocalPosition() - m_target->GetTransform()->GetLocalPosition();


    // ‘ŠŽè‚Ì‘¬“x‚Ìˆê•bŒã‚ÌˆÊ’u‚ð‰ÁŽZ‚·‚é
    float distance = toTargetPosition.Length();
    float speed = m_object->GetVelocity().Length() + 0.01f;

    // æ“Ç‚ÝŽžŠÔ‚ðŒvŽZ
    float lookAheadTime = distance / speed;

    // —\‘ªˆÊ’u‚ðŒvŽZ
    DirectX::SimpleMath::Vector3 futurePos = position + velocity * lookAheadTime;

    DirectX::SimpleMath::Vector3 desired = futurePos - m_object->GetTransform()->GetLocalPosition();
    desired.y = 0.0f;
    desired.Normalize();
    desired *= 2.0f;


    return desired;
}