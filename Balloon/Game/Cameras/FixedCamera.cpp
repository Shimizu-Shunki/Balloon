#include "Framework/pch.h"
#include "Game/Cameras/FixedCamera.h"


FixedCamera::FixedCamera()
	:
	m_transform{},
	m_up{},
	m_view{}
{
}

FixedCamera::~FixedCamera()
{

}

void FixedCamera::Initialize(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& targetPosition,
	const DirectX::SimpleMath::Quaternion& rotation, CameraManager* cameraManager)
{
	// カメラマネージャーのインスタンスを取得する
	m_cameraManager = cameraManager;

	// Transformを作成
	m_transform = std::make_unique<Transform>();

	// 座標を設定する
	m_transform->SetLocalPosition(position);

	// ターゲット座標
	// 回転を設定
	m_transform->SetLocalRotation(rotation);
	// ターゲットは正面
	DirectX::SimpleMath::Vector3 target =
		DirectX::SimpleMath::Vector3::Backward;
	// 回転を適応
	target = DirectX::SimpleMath::Vector3::Transform(target, rotation);

	// ターゲット座標を設定する スケールをターゲットとしてみる
	m_transform->SetLocalScale(position + target);
	// 頭の向きを設定する
	m_up = DirectX::SimpleMath::Vector3::Up;

	// 固定カメラのため初期化の時点のみビュー行列を作成する
	m_cameraManager->SetViewMatrix(this->CalculateViewMatrix());
}

void FixedCamera::Update()
{
	// 固定カメラのため更新はなし
}

DirectX::SimpleMath::Matrix FixedCamera::CalculateViewMatrix()
{
	// ビュー行列を作成
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_transform->GetLocalPosition(), m_transform->GetLocalScale(), m_up);

	return m_view;
}