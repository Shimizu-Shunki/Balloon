#include "Framework/pch.h"
#include "Game/PhysicsBody/PhysicsBody.h"
#include "Framework/CommonResources.h"

PhysicsBody::PhysicsBody(IObject* object)
    : 
    m_object(object),
    m_mass(1.0f),
    m_velocity(DirectX::SimpleMath::Vector3::Zero),
    m_acceleration(DirectX::SimpleMath::Vector3::Zero),
    m_force(DirectX::SimpleMath::Vector3::Zero),
    m_gravity(-9.8f),
    m_useGravity(true),
    m_isKinematic(false)
{
    m_commonResources = CommonResources::GetInstance();
}

// �X�V����
void PhysicsBody::Update()
{
    // �o�ߕb��
    float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

    if (m_mass <= 0.0f) return;  // ����0�͌v�Z���Ȃ�

    // �d�͂̓K�p
    if (m_useGravity)
    {
        m_force.y += m_mass * m_gravity;
    }

    // �����x = �� / ����
    m_acceleration = m_force / m_mass;

    // ���x���X�V
    m_velocity += m_acceleration * elapsedTime;

   

    // **�n�ʂƂ̏Փˏ���**
    if (!m_useGravity)
    {
        // **���������̑��x��0�ɂ���i�����Ȃ��j**
        //m_velocity.y = 0.0f;

        // **�����C��K�p�iX�EZ �����̑��x�������j**
        float frictionCoefficient = 0.9f; // ���C�W���i0�`1�A�������قǊ���j
        m_velocity.x *= frictionCoefficient;
        m_velocity.z *= frictionCoefficient;

        // **�Î~���C��K�p�i�\���x���Ȃ��~�j**
        if (std::abs(m_velocity.x) < 0.01f) m_velocity.x = 0.0f;
        if (std::abs(m_velocity.z) < 0.01f) m_velocity.z = 0.0f;
    }
    else
    {
        // **�����C��K�p�iX�EZ �����̑��x�������j**
        float frictionCoefficient = 0.95f; // ���C�W���i0�`1�A�������قǊ���j
        m_velocity.x *= frictionCoefficient;
        m_velocity.z *= frictionCoefficient;

        // **�Î~���C��K�p�i�\���x���Ȃ��~�j**
        if (std::abs(m_velocity.x) < 0.01f) m_velocity.x = 0.0f;
        if (std::abs(m_velocity.z) < 0.01f) m_velocity.z = 0.0f;
    }

    // ���̐V�����ʒu
    DirectX::SimpleMath::Vector3 newPosition = m_object->GetTransform()->GetLocalPosition() + m_velocity * elapsedTime;

    // �ʒu���X�V
    m_object->GetTransform()->SetLocalPosition(newPosition);

    // �͂����Z�b�g
    m_force = DirectX::SimpleMath::Vector3::Zero;
}