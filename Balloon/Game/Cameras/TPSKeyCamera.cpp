#include "Framework/pch.h"
#include "Game/Cameras/TPSKeyCamera.h"
#include "Game/PhysicsBody/PhysicsBody.h"
#include <Mouse.h>



TPSKeyCamera::TPSKeyCamera(Transform* targetTransform, PhysicsBody* targetPhysicsBody, DirectX::SimpleMath::Vector3 distance)
	:
	m_targetTransform(targetTransform),
	m_targetPhysicsBody(targetPhysicsBody),
	m_distance(distance),
	m_initialRotation{},
	m_up{},
	m_view{},
	m_sensitivity{}
{
}

void TPSKeyCamera::Initialize()
{
	// Transformを作成
	m_transform = std::make_unique<Transform>();

	// 初期化
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::Zero);

	// 頭の向きを設定する
	m_up = DirectX::SimpleMath::Vector3::Up;

	// 感度を設定
	m_sensitivity = 0.0009f;

	m_pitch = 0.0f;

	// 初期回転角を設定
	m_initialRotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(0.78f));

	// マウスを相対モードにする
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void TPSKeyCamera::Update()
{
	// 速度を取得
	DirectX::SimpleMath::Vector3 velocity = m_targetPhysicsBody->GetVelocity();

	DirectX::SimpleMath::Vector3 angle = m_targetTransform->GetLocalRotation().ToEuler();

	// ターゲットの回転を考慮する
	m_yaw  = angle.y + DirectX::XMConvertToRadians(180.0f);

	float targetPitch = BASE_PITCH - (-velocity.y * PITCH_OFFSET_FACTOR);
	// 制限を適用
	targetPitch = std::clamp(targetPitch, MIN_PITCH, MAX_PITCH);
	// 補間 (スムーズな変化) - LERP
	const float interpolationSpeed = 0.03f; // 0.0～1.0の範囲で調整（小さいほどゆっくり補間）
	m_pitch = (1.0f - interpolationSpeed) * m_pitch + interpolationSpeed * targetPitch;

	// ヨー角とピッチ角に基づいてクォータニオンを作成し、現在の角度を更新
	DirectX::SimpleMath::Quaternion rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(m_yaw, m_pitch, 0);

	// 回転を更新
	m_transform->SetLocalRotation(m_initialRotation * rotation);
	

	// ビュー行列を作成
	this->CalculateViewMatrix();
}

// ビュー行列を計算する
DirectX::SimpleMath::Matrix  TPSKeyCamera::CalculateViewMatrix()
{
	// プレイヤーの座標を取得
	DirectX::SimpleMath::Vector3 position = m_targetTransform->GetLocalPosition();

	// 現在の角度に基づいてカメラの距離を変換し、カメラの位置を計算
	DirectX::SimpleMath::Vector3 CameraPosition =
		DirectX::SimpleMath::Vector3::Transform(m_distance, m_transform->GetLocalRotation());

	// 視点 (カメラの位置)
	m_transform->SetLocalPosition(position + CameraPosition);
	// 注視点 (カメラが見る目標の位置) - プレイヤーの位置
	m_transform->SetLocalScale(position);
	
	// ビュー行列を作成
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(
		m_transform->GetLocalPosition(), m_transform->GetLocalScale(), m_up);

	// ビュー行列を設定
	return m_view;
}