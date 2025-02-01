#include "pch.h"
#include "Game/Camera/TPSCamera2.h"
#include "Framework/Graphics.h"
#include "Framework/InputManager.h"

TPSCamera2::TPSCamera2()
{

}

TPSCamera2::~TPSCamera2()
{

}

void TPSCamera2::Initialize()
{
	// ターゲットからの距離
	m_distance = { 0.0f,3.0f,5.0f };

	// 初期化
	m_yaw = 0.0f;
	m_pitch = 0.0f;

	// 感度を設定
	m_sensitivity = 0.0009f;

	// 初期回転角を設定
	m_initial_angle = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(0.78f));

	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void TPSCamera2::Update(float elapsed_time, DirectX::SimpleMath::Vector3 const& position)
{
	// ターゲットの座標
	m_targetObjectPosition = position;

	// マウスの横方向の動きに基づいてヨー角を更新
	m_yaw   -= m_inputManager->GetMouseTracker()->GetLastState().x * m_sensitivity;
	// マウスの縦方向の動きに基づいてピッチ角を更新
	m_pitch -= m_inputManager->GetMouseTracker()->GetLastState().y * m_sensitivity;

	// ヨー角とピッチ角に基づいてクォータニオンを作成し、現在の角度を更新
	DirectX::SimpleMath::Quaternion rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(m_yaw, m_pitch, 0);
	m_current_angle = m_initial_angle * rotation;


	// 下
	if (MIN_VALUE >= position.y)
	{

	}
	// 中央
	else if (MEDIAN_VALUE >= position.y)
	{

	}
	// 上
	else
	{

	}
}

void TPSCamera2::CalculateViewMatrix()
{
	// プレイヤーの座標を取得
	DirectX::SimpleMath::Vector3 position = m_targetObjectPosition;

	// 現在の角度に基づいてカメラの距離を変換し、カメラの位置を計算
	DirectX::SimpleMath::Vector3 camera_position =
		DirectX::SimpleMath::Vector3::Transform(m_distance, m_current_angle);

	// 視点 (カメラの位置)
	m_eye = position + camera_position;

	// 注視点 (カメラが見る目標の位置) - プレイヤーの位置
	m_target = position;
	// カメラの頭
	m_up = DirectX::SimpleMath::Vector3::Up;

	// カメラのビュー行列を作成
	m_graphics->SetViewMatrix(DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up));
}