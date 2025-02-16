#pragma once
#include "Framework/CommonResources.h"
#include "Interface/ICamera.h"


class InputManager;
class IObject;
class Transform;

class TPSCamera : public ICamera
{

public :
	// SET
	// Transformを取得する
	Transform* GetTransform() const override { return m_transform.get(); }

public:
	// ビュー行列を設定する
	DirectX::SimpleMath::Matrix CalculateViewMatrix() override;
public :
	// コンストラクタ
	TPSCamera(IObject* object);
	// デストラクタ
	~TPSCamera();

	
	// 初期化処理
	void Initialize(
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& targetPosition,
		const DirectX::SimpleMath::Quaternion& rotation, CameraManager* cameraManager);
	// 更新処理
	void Update();


private:

	// グラフィックス
	Graphics* m_graphics;
	// インプットマネージャー
	InputManager* m_inputManager;
	// 追跡するオブジェクト
	IObject* m_targetObject;

	std::unique_ptr<Transform> m_transform;

	// カメラマネージャー
	CameraManager* m_cameraManager;
	

	// 座標
	DirectX::SimpleMath::Vector3 m_position;
	// 初期回転角
	DirectX::SimpleMath::Quaternion m_initialRotation;
	// 現在の回転角
	DirectX::SimpleMath::Quaternion m_currentRotation;
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
	// 感度
	float m_sensitivity;
	// 横回転（Ｙ軸回転）
	float m_pitch;
	// 縦回転（Ｘ軸回転）
	float m_yaw;
};
