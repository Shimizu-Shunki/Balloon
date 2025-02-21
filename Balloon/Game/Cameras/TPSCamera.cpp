#include "Framework/pch.h"
#include "Game/Cameras/TPSCamera.h"
#include <Mouse.h>

#include "Framework/InputManager.h"

TPSCamera::TPSCamera(Transform* targetTransform, DirectX::SimpleMath::Vector3 distance)
	:
	m_targetTransform(targetTransform),
	m_distance(distance),
	m_initialRotation{},
	m_up{},
	m_view{},
	m_sensitivity{},
	m_pitch{},
	m_yaw{}
{
	// インプットマネージャーのインスタンスを取得する
	m_inputManager = InputManager::GetInstance();
}

void TPSCamera::Initialize()
{
	// Transformを作成
	m_transform = std::make_unique<Transform>();

	// 初期化
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::Zero);

	// 頭の向きを設定する
	m_up = DirectX::SimpleMath::Vector3::Up;

	// 初期化
	m_yaw   = 0.0f;
	m_pitch = 0.0f;

	// 感度を設定
	m_sensitivity = 0.0009f;

	// 初期回転角を設定
	m_initialRotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(0.78f));

	// マウスを相対モードにする
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void TPSCamera::Update()
{
	// マウスステート
	const DirectX::Mouse::State& mouseState = m_inputManager->GetMouse()->GetState();

	if (mouseState.positionMode == DirectX::Mouse::MODE_RELATIVE)
	{
		// マウスの横方向の動きに基づいてヨー角を更新
		m_yaw   -= m_inputManager->GetMouseTracker()->GetLastState().x * m_sensitivity;
		// マウスの縦方向の動きに基づいてピッチ角を更新
		m_pitch -= m_inputManager->GetMouseTracker()->GetLastState().y * m_sensitivity;

		// ピッチ角の制限: -90度から90度
		const float pitchLimit = DirectX::XM_PIDIV2 - 0.01f; // 90度 - マージン
		m_pitch = std::clamp(m_pitch, -pitchLimit, pitchLimit);

		// ヨー角とピッチ角に基づいてクォータニオンを作成し、現在の角度を更新
		DirectX::SimpleMath::Quaternion rotation =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(m_yaw, m_pitch, 0);

		// 回転を更新
		m_transform->SetLocalRotation(m_initialRotation * rotation);
	}

	// ビュー行列を作成
	this->CalculateViewMatrix();

#ifdef _DEBUG
	// マウスモードを絶対モード
	if (m_inputManager->OnKeyDown(InputManager::Keys::W))
	{
		DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_ABSOLUTE);
	}
	// マウスモードを総体モード
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
	}
#endif
}

// ビュー行列を計算する
DirectX::SimpleMath::Matrix  TPSCamera::CalculateViewMatrix()
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