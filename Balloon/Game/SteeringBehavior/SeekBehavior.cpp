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

    // ����̍��W
    const DirectX::SimpleMath::Vector3 position = m_target->GetTransform()->GetLocalPosition();
    // ����̑��x
    const DirectX::SimpleMath::Vector3 velocity = m_target->GetVelocity();

    // ����̌������v�Z
    const DirectX::SimpleMath::Vector3 toTargetPosition =
        m_object->GetTransform()->GetLocalPosition() - m_target->GetTransform()->GetLocalPosition();


    // ����̑��x�̈�b��̈ʒu�����Z����
    float distance = toTargetPosition.Length();
    float speed = m_object->GetVelocity().Length() + 0.01f;

    // ��ǂݎ��Ԃ��v�Z
    float lookAheadTime = distance / speed;

    // �\���ʒu���v�Z
    DirectX::SimpleMath::Vector3 futurePos = position + velocity * lookAheadTime;

    DirectX::SimpleMath::Vector3 desired = futurePos - m_object->GetTransform()->GetLocalPosition();
    desired.y = 0.0f;
    desired.Normalize();
    desired *= 2.0f;


    return desired;
}