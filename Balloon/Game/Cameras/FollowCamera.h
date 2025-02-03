#pragma once
#include "Interface/ICamera.h"

class Transform;
class CameraManager;

class FollowCamera : public ICamera
{
public:
	// Transformを取得する
	Transform* GetTransform() const { return m_transform.get(); }

public:
	// ビュー行列を設定する
	DirectX::SimpleMath::Matrix CalculateViewMatrix() override;
public:
	// コンストラクタ
	FollowCamera(Transform* target,DirectX::SimpleMath::Vector3 distance);
	// デストラクタ
	~FollowCamera() override;

public:

	// 初期化処理
	void Initialize(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& targetPosition,
		const DirectX::SimpleMath::Quaternion& rotation , CameraManager* cameraManager) override;
	// 更新処理
	void Update() override;

private:

	// カメラマネージャー
	CameraManager* m_cameraManager;

	// Transform
	std::unique_ptr<Transform> m_transform;
	// ターゲット
	Transform* m_targetTransform;
	// 頭の向き
	DirectX::SimpleMath::Vector3 m_up;

	// 視点から注視点までの距離
	DirectX::SimpleMath::Vector3 m_distance;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;

};