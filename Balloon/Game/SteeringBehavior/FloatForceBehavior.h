#pragma once
#include "Interface/ISteeringBehavior.h"

class IObject;


class FloatForceBehavior : public ISteeringBehavior
{
public:
    // 0～1の強さ設定
    void SetForceStrength(const float& strength) { m_forceStrength = strength; }

    // ステアリング力を計算する
    DirectX::SimpleMath::Vector3 Calculate() override;


    FloatForceBehavior(IObject* object);
    ~FloatForceBehavior() override = default;

private:

    IObject* m_object;

    float m_forceStrength;
};