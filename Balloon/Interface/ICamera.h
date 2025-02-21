#pragma once
#ifndef ICAMERA_DEFINED
#define IICAMERA_DEFINED
#include "Framework/pch.h"
#include "Framework/StepTimer.h"
#include "Interface/IObject.h"
#include "Game/Transform/Transform.h"
#include "Framework/CameraManager.h"

class CameraManager;

class ICamera
{
public:
	// Transformを取得する
	virtual Transform* GetTransform() const = 0;
	// ビュー行列を作成する
	virtual DirectX::SimpleMath::Matrix GetViewMatrix() const = 0;

public:
	// 仮想デストラクタ
	virtual ~ICamera() = default;
	// 初期化処理
	virtual void Initialize() = 0;
	// 更新処理
	virtual void Update() = 0;
	// ビュー行列の作成
	virtual DirectX::SimpleMath::Matrix CalculateViewMatrix() = 0;
};


#endif		// ICAMERA_DEFINED