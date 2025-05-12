#pragma once
#include "Interface/ISteeringBehavior.h"

class IObject;


class FloatForceBehavior : public ISteeringBehavior
{
public:
    // 0�`1�̋����ݒ�
    void SetForceStrength(const float& strength) { m_forceStrength = strength; }

    // �X�e�A�����O�͂��v�Z����
    DirectX::SimpleMath::Vector3 Calculate() override;


    FloatForceBehavior(IObject* object);
    ~FloatForceBehavior() override = default;

private:

    IObject* m_object;

    float m_forceStrength;
};