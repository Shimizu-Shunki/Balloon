#pragma once
#include "Interface/ICamera.h"

class Graphics;
class Transform;

class FixedCamera : public ICamera
{
public:
	// Transformを取得する
	Transform* GetTransform() const override { return m_transform.get(); }

public:
	// ビュー行列を設定する
	DirectX::SimpleMath::Matrix CalculateViewMatrix() override;
public:
	// コンストラクタ
	FixedCamera();

	// デストラクタ
	~FixedCamera() override;

public:

	// 初期化処理
	void Initialize(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& targetPosition,
		const DirectX::SimpleMath::Quaternion& rotation, CameraManager* cameraManager) override;
	// 更新処理
	void Update() override;

private:

	// カメラマネージャー
	CameraManager* m_cameraManager;

	// Transform Scaleをターゲットとして見る
	std::unique_ptr<Transform> m_transform;
	// 頭の向き
	DirectX::SimpleMath::Vector3 m_up;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	
};