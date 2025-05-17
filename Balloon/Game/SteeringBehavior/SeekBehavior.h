#pragma once
#include "Interface/ISteeringBehavior.h"

class Object;


class SeekBehavior : public ISteeringBehavior
{
public:
    // 0�`1�̋����ݒ�
    void SetForceStrength(const float& strength) { m_forceStrength = strength; }

    // �X�e�A�����O�͂��v�Z����
    DirectX::SimpleMath::Vector3 Calculate() override;


    SeekBehavior(Object* object , Object* target);
    ~SeekBehavior() override = default;

private:

    // �ǔ�����I�u�W�F�N�g
    Object* m_target;

    // �I�u�W�F�N�g
    Object* m_object;





    float m_forceStrength;
};