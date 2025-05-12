#pragma once
#include "Interface/ISteeringBehavior.h"


class PushBackBehavior : public ISteeringBehavior
{
public:

    // ステアリング力を計算する
    DirectX::SimpleMath::Vector3 Calculate() override;

    PushBackBehavior(IObject* object);
    ~PushBackBehavior() override = default;

private:

    // 対象オブジェクト
    IObject* m_object;     

    // ステージ最小座標
    DirectX::SimpleMath::Vector3 m_stageMinBounds; 
    // ステージ最大座標
    DirectX::SimpleMath::Vector3 m_stageMaxBounds;  
    // 押し戻し力
    float m_pushBackStrength;                     
};