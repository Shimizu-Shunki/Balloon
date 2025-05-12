#include "pch.h"
#include  "Game/SteeringBehavior/FloatBehavior.h"
#include "Framework/CommonResources.h"

FloatBehavior::FloatBehavior()
{
	m_amplitude = 2.0f;
	m_floatSpeed = 1.0f;
	m_isFloat = false;
	m_elapsedTime = 0.0f;
}


DirectX::SimpleMath::Vector3 FloatBehavior::Calculate()
{
	float elapsedTime = (float)CommonResources::GetInstance()->GetStepTimer()->GetElapsedSeconds();

	m_elapsedTime += elapsedTime;

	if (!m_isFloat) return DirectX::SimpleMath::Vector3::Zero;

	float wave = std::sin(m_elapsedTime * 1.0f * 2.0f * DirectX::XM_PI) * m_amplitude;

	return DirectX::SimpleMath::Vector3(0.0f, wave, 0.0f);
}


void FloatBehavior::On(float centerY)
{
	// センターの位置を設定
	m_centerY = centerY;
	// フラグをオンにする
	m_isFloat = true;
}

void FloatBehavior::Off()
{
	// センター位置をリセット
	m_centerY = 0.0f;
	// フラグをオフにする
	m_isFloat = false;
}

