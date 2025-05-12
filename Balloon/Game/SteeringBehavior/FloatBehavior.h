#pragma once
#include "Interface/ISteeringBehavior.h"


class FloatBehavior : public ISteeringBehavior
{

public:

	void On(float centerY);

	void Off();

	// ステアリング力を計算する
	DirectX::SimpleMath::Vector3 Calculate() override;

	FloatBehavior();
	~FloatBehavior() override = default;

private:

	// 揺れているかのフラグ
	bool m_isFloat;

	// 揺れる高さの最大値
	float m_amplitude;

	// 揺れるスピード
	float m_floatSpeed;

	// 経過時間
	float m_elapsedTime;

	// 揺れる中心位置
	float m_centerY;

};