#include "Framework/pch.h"
#include "Game/Cameras/FollowCamera.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="target">追従対象となるオブジェクトの Transform ポインタ</param>
/// <param name="distance">ターゲットとの相対的な位置（オフセット距離）</param>
FollowCamera::FollowCamera(Transform* target, DirectX::SimpleMath::Vector3 distance)
	:
	m_targetTransform(target),
	m_distance(distance),
	m_transform{},
	m_up{},
	m_view{}
{
}

/// <summary>
/// 初期化処理
/// </summary>
void FollowCamera::Initialize()
{
	// Transformを作成
	m_transform = std::make_unique<Transform>();

	// 初期化
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::Zero);

	// 頭の向きを設定する
	m_up = DirectX::SimpleMath::Vector3::Up;

	// ビュー行列を作成
	this->CalculateViewMatrix();
}

/// <summary>
/// 更新処理
/// </summary>
void FollowCamera::Update()
{
	// ビュー行列を更新
	this->CalculateViewMatrix();
}

/// <summary>
/// ビュー行列を作成
/// </summary>
/// <returns>ビュー行列</returns>
DirectX::SimpleMath::Matrix FollowCamera::CalculateViewMatrix()
{
	// プレイヤーの座標を取得
	DirectX::SimpleMath::Vector3 position = m_targetTransform->GetLocalPosition();

	// 現在の角度に基づいてカメラの距離を変換し、カメラの位置を計算
	DirectX::SimpleMath::Vector3 CameraPosition =
		DirectX::SimpleMath::Vector3::Transform(m_distance, m_targetTransform->GetLocalRotation());

	// 視点 (カメラの位置)
	m_transform->SetLocalPosition(position + CameraPosition);

	// 注視点 (カメラが見る目標の位置) - プレイヤーの位置
	m_transform->SetLocalScale(position);

	// ビュー行列を作成
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_transform->GetLocalPosition(), m_transform->GetLocalScale(), m_up);

	return m_view;
}