#pragma once
#ifndef ICAMERA_DEFINED
#define IICAMERA_DEFINED
#include "pch.h"
#include "StepTimer.h"
#include "Interface/IComponent.h"


class ICamera
{
public:
	// SET
	// カメラ座標を設定する
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;
	// ターゲット座標を設定する
	virtual void SetTargetPosition(const DirectX::SimpleMath::Vector3& targetPosition) = 0;
	// 回転角を設定する
	virtual void SetRotation(const DirectX::SimpleMath::Quaternion& rotation) = 0;
	

	// GET
	// カメラ座標を取得する
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	// ターゲット座標を取得する
	virtual DirectX::SimpleMath::Vector3 GetTargetPosition() const = 0;
	// 回転角を取得する
	virtual DirectX::SimpleMath::Quaternion GetRotation() const = 0;
	// ビュー行列を取得する
	virtual DirectX::SimpleMath::Matrix GetViewMatrinx() const = 0;


public:
	// 仮想デストラクタ
	virtual ~ICamera() = default;
	// 初期化処理
	virtual void Initialize(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& targetPosition,
		const DirectX::SimpleMath::Quaternion& rotation) = 0;
	// 更新処理
	virtual void Update(const float& deltaTime) = 0;
	// ビュー行列の作成
	virtual void CalculateViewMatrix() = 0;
};


#endif		// ICAMERA_DEFINED