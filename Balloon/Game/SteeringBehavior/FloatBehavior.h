#pragma once
#include "Interface/ISteeringBehavior.h"


class FloatBehavior : public ISteeringBehavior
{

public:

	void On(float centerY);

	void Off();

	// �X�e�A�����O�͂��v�Z����
	DirectX::SimpleMath::Vector3 Calculate() override;

	FloatBehavior();
	~FloatBehavior() override = default;

private:

	// �h��Ă��邩�̃t���O
	bool m_isFloat;

	// �h��鍂���̍ő�l
	float m_amplitude;

	// �h���X�s�[�h
	float m_floatSpeed;

	// �o�ߎ���
	float m_elapsedTime;

	// �h��钆�S�ʒu
	float m_centerY;

};