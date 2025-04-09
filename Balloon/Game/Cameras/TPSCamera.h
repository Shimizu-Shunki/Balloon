// ============================================
// 
// ファイル名: TPSCamera.h
// 概要: TPSCamera.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/ICamera.h"

class InputManager;
class Transform;

class TPSCamera : public ICamera
{

public :
	// Transformを取得する
	Transform* GetTransform() const override { return m_transform.get(); }
	// ビュー行列を取得する
	DirectX::SimpleMath::Matrix GetViewMatrix() const override { return m_view; }


public:
	// ビュー行列を設定する
	DirectX::SimpleMath::Matrix CalculateViewMatrix() override;
public :
	// コンストラクタ
	TPSCamera(Transform* targetTransform , DirectX::SimpleMath::Vector3 distance);
	// デストラクタ
	~TPSCamera() override = default;

	
	// 初期化処理
	void Initialize() override;
	// 更新処理
	void Update() override;

private:
	// インプットマネージャー
	InputManager* m_inputManager;

	// Trasform
	std::unique_ptr<Transform> m_transform;
	// 頭の向き
	DirectX::SimpleMath::Vector3 m_up;
	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// 追跡するTransform
	Transform* m_targetTransform;
	// 初期回転角
	DirectX::SimpleMath::Quaternion m_initialRotation;


	// 視点から注視点までの距離
	DirectX::SimpleMath::Vector3 m_distance;
	// 感度
	float m_sensitivity;
	// 横回転（Ｙ軸回転）
	float m_pitch;
	// 縦回転（Ｘ軸回転）
	float m_yaw;
};
