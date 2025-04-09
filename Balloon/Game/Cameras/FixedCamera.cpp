// ============================================
// 
// ファイル名: FixedCamera.cpp
// 概要: 固定カメラ
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Cameras/FixedCamera.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
FixedCamera::FixedCamera(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotation)
	:
	m_transform{},
	m_up{},
	m_view{}
{
	// Transformを作成
	m_transform = std::make_unique<Transform>();

	// 座標を設定
	m_transform->SetLocalPosition(position);
	// 回転を設定
	m_transform->SetLocalRotation(rotation);
}

/// <summary>
/// 初期化処理
/// </summary>
void FixedCamera::Initialize()
{
	// ターゲットは正面
	DirectX::SimpleMath::Vector3 target =
		DirectX::SimpleMath::Vector3::Backward;
	// 回転を適応
	target = DirectX::SimpleMath::Vector3::Transform(target, m_transform->GetLocalRotation());

	// ターゲット座標を設定する スケールをターゲットとしてみる
	m_transform->SetLocalScale(m_transform->GetLocalPosition() + target);
	// 頭の向きを設定する
	m_up = DirectX::SimpleMath::Vector3::Up;

	// ビュー行列を作成
	this->CalculateViewMatrix();
}

/// <summary>
/// 更新処理
/// </summary>
void FixedCamera::Update()
{
	// 固定カメラのため更新はなし
}

/// <summary>
/// ビュー行列を作成
/// </summary>
/// <returns>ビュー行列</returns>
DirectX::SimpleMath::Matrix FixedCamera::CalculateViewMatrix()
{
	// ビュー行列を作成
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_transform->GetLocalPosition(), m_transform->GetLocalScale(), m_up);

	return m_view;
}