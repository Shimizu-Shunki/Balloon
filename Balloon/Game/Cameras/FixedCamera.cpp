#include "pch.h"
#include "Game/Camera/FixedCamera.h"
#include "Framework/Graphics.h"

FixedCamera::FixedCamera()
	:
	m_position{},
	m_targetPosition{},
	m_rotation{},
	m_up{},
	m_view{}
{
	// グラフィックのインスタンスを取得する
	m_graphics = Graphics::GetInstance();
}

FixedCamera::~FixedCamera()
{

}

void FixedCamera::Initialize(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& targetPosition,
	const DirectX::SimpleMath::Quaternion& rotation)
{
	// 座標を設定する
	m_position = position;
	// ターゲット座標を設定する
	m_targetPosition = targetPosition;
	// 回転角を設定する
	m_rotation = rotation;
	// 頭の向きを設定する
	m_up = DirectX::SimpleMath::Vector3::Up;

	// 固定カメラのため初期化の時点のみビュー行列を作成する
	this->CalculateViewMatrix();
}

void FixedCamera::Update(const float& deltaTime)
{
	// 固定カメラのため更新はなし
}

void FixedCamera::CalculateViewMatrix()
{
	// ビュー行列を作成
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_position, m_targetPosition, m_up);
	// ビュー行列を設定
	m_graphics->SetViewMatrix(m_view);
}