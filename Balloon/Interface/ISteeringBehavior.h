#pragma once
#include "Game/Object/Object.h"

class ISteeringBehavior
{
public:
    virtual ~ISteeringBehavior() = default;

    /// ステアリング力を計算
    virtual DirectX::SimpleMath::Vector3 Calculate()  = 0;
};