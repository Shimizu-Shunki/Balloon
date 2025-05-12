#pragma once
#include "Interface/ISteeringBehavior.h"


class PushBackBehavior : public ISteeringBehavior
{
public:

    // �X�e�A�����O�͂��v�Z����
    DirectX::SimpleMath::Vector3 Calculate() override;

    PushBackBehavior(IObject* object);
    ~PushBackBehavior() override = default;

private:

    // �ΏۃI�u�W�F�N�g
    IObject* m_object;     

    // �X�e�[�W�ŏ����W
    DirectX::SimpleMath::Vector3 m_stageMinBounds; 
    // �X�e�[�W�ő���W
    DirectX::SimpleMath::Vector3 m_stageMaxBounds;  
    // �����߂���
    float m_pushBackStrength;                     
};