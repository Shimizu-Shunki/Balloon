#pragma once
#include "Interface/ICamera.h"

class Graphics;

class FixedCamera : public ICamera
{
public:
	// SET
	// カメラ座標を設定する
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_position = position; }
	// ターゲット座標を設定する
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& targetPosition) override { m_targetPosition = targetPosition; }
	// 回転角を設定する
	void SetRotation(const DirectX::SimpleMath::Quaternion& rotation) override { m_rotation = rotation; }


	// GET
	// カメラ座標を取得する
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_position; }
	// ターゲット座標を取得する
	DirectX::SimpleMath::Vector3 GetTargetPosition() const override { return m_targetPosition; }
	// 回転角を取得する
	DirectX::SimpleMath::Quaternion GetRotation() const override { return m_rotation; }
	// ビュー行列を取得する
	DirectX::SimpleMath::Matrix GetViewMatrinx() const override { return m_view; }

public:
	// ビュー行列を設定する
	void CalculateViewMatrix() override;
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
		const DirectX::SimpleMath::Quaternion& rotation) override;
	// 更新処理
	void Update(const float& deltaTime) override;

private:

	// グラフィックス
	Graphics* m_graphics;

	// 座標
	DirectX::SimpleMath::Vector3 m_position;
	// 回転角
	DirectX::SimpleMath::Quaternion m_rotation;
	// ターゲット座標
	DirectX::SimpleMath::Vector3 m_targetPosition;
	// 頭の向き
	DirectX::SimpleMath::Vector3 m_up;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	
};