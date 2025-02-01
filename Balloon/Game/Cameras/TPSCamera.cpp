#include "pch.h"
#include "Game/Camera/TPSCamera.h"

#include "Framework/Graphics.h"
#include "Framework/InputManager.h"

TPSCamera::TPSCamera()
	:
	m_position{},
	m_initialRotation{},
	m_currentRotation{},
	m_targetPosition{},
	m_up{},
	m_distance{},
	m_targetObjectPosition{},
	m_view{},
	m_sensitivity{},
	m_pitch{},
	m_yaw{}
{
	// グラフィックスのインスタンスを取得する
	m_graphics = Graphics::GetInstance();
	// インプットマネージャーのインスタンスを取得する
	m_inputManager = InputManager::GetInstance();
}


TPSCamera::~TPSCamera()
{

}


void TPSCamera::Initialize(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& targetPosition,
	const DirectX::SimpleMath::Quaternion& rotation)
{
	// ターゲットからの距離
	m_distance = { 0.0f,5.0f, 7.0f };

	// 初期化
	m_yaw = 0.0f;
	m_pitch = 0.0f;

	// 感度を設定
	m_sensitivity = 0.0009f;

	// 初期回転角を設定
	m_initialRotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(0.78f));

	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void TPSCamera::Update(const float& deltaTime)
{
	m_targetObjectPosition = m_targetObject->GetPosition();

	if (m_inputManager->GetMouseState().positionMode == DirectX::Mouse::MODE_RELATIVE)
	{
		// マウスの横方向の動きに基づいてヨー角を更新
		m_yaw   -= m_inputManager->GetMouseTracker()->GetLastState().x * m_sensitivity;
		// マウスの縦方向の動きに基づいてピッチ角を更新
		m_pitch -= m_inputManager->GetMouseTracker()->GetLastState().y * m_sensitivity;

		// ヨー角とピッチ角に基づいてクォータニオンを作成し、現在の角度を更新
		DirectX::SimpleMath::Quaternion rotation =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(m_yaw, m_pitch, 0);
		m_currentRotation = m_initialRotation * rotation;
	}

	// 固定カメラのため初期化の時点のみビュー行列を作成する
	this->CalculateViewMatrix();

#ifdef _DEBUG
	// マウスモードを絶対モード
	if (m_inputManager->GetKeyboardTracker()->IsKeyPressed(DirectX::Keyboard::X))
	{
		DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_ABSOLUTE);
	}
	// マウスモードを総体モード
	if (m_inputManager->GetKeyboardTracker()->IsKeyPressed(DirectX::Keyboard::Z))
	{
		DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
	}
#endif
}

// ビュー行列を計算する
void TPSCamera::CalculateViewMatrix()
{
	// プレイヤーの座標を取得
	DirectX::SimpleMath::Vector3 position = m_targetObjectPosition;

	// 現在の角度に基づいてカメラの距離を変換し、カメラの位置を計算
	DirectX::SimpleMath::Vector3 camera_position =
		DirectX::SimpleMath::Vector3::Transform(m_distance, m_currentRotation);

	// 視点 (カメラの位置)
	m_position = position + camera_position;

	// 注視点 (カメラが見る目標の位置) - プレイヤーの位置
	m_targetPosition = position;
	// カメラの頭
	m_up = DirectX::SimpleMath::Vector3::Up;

	// ビュー行列を作成
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_position, m_targetPosition, m_up);
	// ビュー行列を設定
	m_graphics->SetViewMatrix(m_view);
}