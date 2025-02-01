#pragma once
#include "Interface/ICamera.h"

class Graphics;

class FollowCamera : public ICamera
{
public:
	// SET
	// カメラ座標を設定する
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_position = position; }
	// ターゲット座標を設定する
	void SetTargetPosition(const DirectX::SimpleMath::Vector3& targetPosition) override { m_targetPosition = targetPosition; }
	// 回転角を設定する
	void SetRotation(const DirectX::SimpleMath::Quaternion& rotation) override { m_rotation = rotation; }

	void SetTargetObject(IComponent* object) { m_targetObject = object; }

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
	FollowCamera(DirectX::SimpleMath::Vector3 distance);

	// デストラクタ
	~FollowCamera() override;

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

	// 追跡するオブジェクト
	IComponent* m_targetObject;

	// 座標
	DirectX::SimpleMath::Vector3 m_position;
	// 回転角
	DirectX::SimpleMath::Quaternion m_rotation;
	// ターゲット座標
	DirectX::SimpleMath::Vector3 m_targetPosition;
	// 頭の向き
	DirectX::SimpleMath::Vector3 m_up;

	// 視点から注視点までの距離
	DirectX::SimpleMath::Vector3 m_distance;
	// 注視するオブジェクトの座標
	DirectX::SimpleMath::Vector3 m_targetObjectPosition;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;

};