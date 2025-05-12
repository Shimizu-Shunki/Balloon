#include "pch.h"
#include "Game/SteeringBehavior/PushBackBehavior.h"
#include "Interface/IObject.h"


PushBackBehavior::PushBackBehavior(IObject* object)
    :
    m_object(object)
{
    m_pushBackStrength = 10.0f;
    m_stageMinBounds = { -5.0f , -5.0f , -5.0f };
    m_stageMaxBounds = { 5.0f , 5.0f , 5.0f };
}


DirectX::SimpleMath::Vector3 PushBackBehavior::Calculate()  
{

    if (!m_object)
    {
        return DirectX::SimpleMath::Vector3::Zero;
    }

    DirectX::SimpleMath::Vector3 force = DirectX::SimpleMath::Vector3::Zero;

    DirectX::SimpleMath::Vector3 position = m_object->GetTransform()->GetLocalPosition();

    if (position.x < m_stageMinBounds.x) 
    {
        force.x = m_pushBackStrength;
    }
    else if (position.x > m_stageMaxBounds.x) 
    {
        force.x = -m_pushBackStrength;
    }

    if (position.y < m_stageMinBounds.y)
    {
        force.y = m_pushBackStrength;
    }
    else if (position.y > m_stageMaxBounds.y)
    {
        force.y = -m_pushBackStrength;
    }

    if (position.z < m_stageMinBounds.z) 
    {
        force.z = m_pushBackStrength;
    }
    else if (position.z > m_stageMaxBounds.z) 
    {
        force.z = -m_pushBackStrength;
    }

    return force;
}