#include "pch.h"
#include "Game/SteeringBehavior/FloatForceBehavior.h"


FloatForceBehavior::FloatForceBehavior(IObject* object)
{
    m_object = object;
}


DirectX::SimpleMath::Vector3 FloatForceBehavior::Calculate()
{
    if (!m_object) 
    {
        return DirectX::SimpleMath::Vector3::Zero;
    }

    float currentHeight = m_object->GetTransform()->GetLocalPosition().y;

    DirectX::SimpleMath::Vector3 force = DirectX::SimpleMath::Vector3::Zero;

    force = DirectX::SimpleMath::Vector3::UnitY * m_forceStrength;

    return force;
}