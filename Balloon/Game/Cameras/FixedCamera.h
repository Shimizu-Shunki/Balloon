// ============================================
// 
// ファイル名: FixedCamera.h
// 概要: FixedCamera.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/ICamera.h"

class Graphics;
class Transform;

class FixedCamera : public ICamera
{
public:
	// Transformを取得する
	Transform* GetTransform() const override { return m_transform.get(); }
	// ビュー行列を取得する
	DirectX::SimpleMath::Matrix GetViewMatrix() const { return m_view; }

	// ビュー行列を設定する
	DirectX::SimpleMath::Matrix CalculateViewMatrix() override;
public:
	// コンストラクタ
	FixedCamera(const DirectX::SimpleMath::Vector3& position , const DirectX::SimpleMath::Quaternion& rotation);
	// デストラクタ
	~FixedCamera() override = default;

	// 初期化処理
	void Initialize() override;
	// 更新処理
	void Update() override;

private:
	// Transform Scaleをターゲットとして見る
	std::unique_ptr<Transform> m_transform;
	// 頭の向き
	DirectX::SimpleMath::Vector3 m_up;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
};