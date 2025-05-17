#pragma once
#include "Interface/ISteeringBehavior.h"

class Object;


class SeekBehavior : public ISteeringBehavior
{
public:
    // 0～1の強さ設定
    void SetForceStrength(const float& strength) { m_forceStrength = strength; }

    // ステアリング力を計算する
    DirectX::SimpleMath::Vector3 Calculate() override;


    SeekBehavior(Object* object , Object* target);
    ~SeekBehavior() override = default;

private:

    // 追尾するオブジェクト
    Object* m_target;

    // オブジェクト
    Object* m_object;





    float m_forceStrength;
};