#pragma once
#include "Game/Object/Object.h"

class ISteeringBehavior
{
public:
    virtual ~ISteeringBehavior() = default;

    /// �X�e�A�����O�͂��v�Z
    virtual DirectX::SimpleMath::Vector3 Calculate()  = 0;
};