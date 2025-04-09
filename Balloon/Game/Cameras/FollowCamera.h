// ============================================
// 
// ファイル名: FollowCamera.h
// 概要: FollowCamera.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/ICamera.h"

class Transform;


class FollowCamera : public ICamera
{
public:
	// Transformを取得する
	Transform* GetTransform() const { return m_transform.get(); }
	// ビュー行列を取得する
	DirectX::SimpleMath::Matrix GetViewMatrix() const override { return m_view; }

public:
	// ビュー行列を設定する
	DirectX::SimpleMath::Matrix CalculateViewMatrix() override;
public:
	// コンストラクタ
	FollowCamera(Transform* target,DirectX::SimpleMath::Vector3 distance);
	// デストラクタ
	~FollowCamera() override = default;

public:

	// 初期化処理
	void Initialize() override;
	// 更新処理
	void Update() override;

private:
	// Transform
	std::unique_ptr<Transform> m_transform;
	// 頭の向き
	DirectX::SimpleMath::Vector3 m_up;
	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// ターゲット
	Transform* m_targetTransform;
	// 視点から注視点までの距離
	DirectX::SimpleMath::Vector3 m_distance;
};