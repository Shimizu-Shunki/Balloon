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

// 更新処理
void PhysicsBody::Update()
{
    // 経過秒数
    float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

    if (m_mass <= 0.0f) return;  // 質量0は計算しない

    // 重力の適用
    if (m_useGravity)
    {
        m_force.y += m_mass * m_gravity;
    }

    // 加速度 = 力 / 質量
    m_acceleration = m_force / m_mass;

    // 速度を更新
    m_velocity += m_acceleration * elapsedTime;

   

    // **地面との衝突処理**
    if (!m_useGravity)
    {
        // **垂直方向の速度を0にする（反発なし）**
        //m_velocity.y = 0.0f;

        // **動摩擦を適用（X・Z 方向の速度を減衰）**
        float frictionCoefficient = 0.9f; // 摩擦係数（0～1、小さいほど滑る）
        m_velocity.x *= frictionCoefficient;
        m_velocity.z *= frictionCoefficient;

        // **静止摩擦を適用（十分遅いなら停止）**
        if (std::abs(m_velocity.x) < 0.01f) m_velocity.x = 0.0f;
        if (std::abs(m_velocity.z) < 0.01f) m_velocity.z = 0.0f;
    }
    else
    {
        // **動摩擦を適用（X・Z 方向の速度を減衰）**
        float frictionCoefficient = 0.95f; // 摩擦係数（0～1、小さいほど滑る）
        m_velocity.x *= frictionCoefficient;
        m_velocity.z *= frictionCoefficient;

        // **静止摩擦を適用（十分遅いなら停止）**
        if (std::abs(m_velocity.x) < 0.01f) m_velocity.x = 0.0f;
        if (std::abs(m_velocity.z) < 0.01f) m_velocity.z = 0.0f;
    }

    // 仮の新しい位置
    DirectX::SimpleMath::Vector3 newPosition = m_object->GetTransform()->GetLocalPosition() + m_velocity * elapsedTime;

    // 位置を更新
    m_object->GetTransform()->SetLocalPosition(newPosition);

    // 力をリセット
    m_force = DirectX::SimpleMath::Vector3::Zero;
}