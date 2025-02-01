#include "pch.h"
#include "Game/Camera/FollowCamera.h"
#include "Game/Camera/FollowCamera.h"
#include "Framework/Graphics.h"

FollowCamera::FollowCamera(DirectX::SimpleMath::Vector3 distance)
	:
	m_distance(distance),
	m_position{},
	m_targetPosition{},
	m_rotation{},
	m_up{},
	m_view{}
{
	// グラフィックのインスタンスを取得する
	m_graphics = Graphics::GetInstance();
}

FollowCamera::~FollowCamera()
{

}

void FollowCamera::Initialize(
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

void FollowCamera::Update(const float& deltaTime)
{
	// ターゲットの座標を設定
	m_targetObjectPosition = m_targetObject->GetPosition();
	// ターゲットの回転角を設定
	m_rotation = m_targetObject->GetAngle();
	// 固定カメラのため初期化の時点のみビュー行列を作成する
	this->CalculateViewMatrix();
}

void FollowCamera::CalculateViewMatrix()
{
	// プレイヤーの座標を取得
	DirectX::SimpleMath::Vector3 position = m_targetObjectPosition;

	// 現在の角度に基づいてカメラの距離を変換し、カメラの位置を計算
	DirectX::SimpleMath::Vector3 camera_position =
		DirectX::SimpleMath::Vector3::Transform(m_distance, m_rotation);

	// 視点 (カメラの位置)
	//m_position = position + camera_position;

	// 注視点 (カメラが見る目標の位置) - プレイヤーの位置
	m_targetPosition = position;
	// カメラの頭
	m_up = DirectX::SimpleMath::Vector3::Up;

	// ビュー行列を作成
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_position, m_targetPosition, m_up);
	// ビュー行列を設定
	m_graphics->SetViewMatrix(m_view);
}