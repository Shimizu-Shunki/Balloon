#pragma once
// 視点を左右キーで回転　ステージの上の方にいるときは上から見下ろす形、ステージの真ん中あたりにいるときは中央から、ステージの下の方にいるときは下から　上下キーで前後移動

class Graphics;
class InputManager;

class TPSCamera2
{
private:
	const int MIN_VALUE    = 4 ;
	const int MEDIAN_VALUE = 8 ;
	const int MAX_VALUE    = 16;


public:
	// コンストラクタ
	TPSCamera2();
	// デストラクタ
	~TPSCamera2();

public:

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update(float elapsed_time, DirectX::SimpleMath::Vector3 const& position);
	// ビュー行列計算処理
	void CalculateViewMatrix();

private:

	// グラフィックス
	Graphics* m_graphics;
	// インプットマネージャー
	InputManager* m_inputManager;

	// 視点
	DirectX::SimpleMath::Vector3 m_eye;
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	// 頭の向き
	DirectX::SimpleMath::Vector3 m_up;

	// 視点から注視点までの距離
	DirectX::SimpleMath::Vector3 m_distance;

	// 横回転（Ｙ軸回転）
	float m_pitch;
	// 縦回転（Ｘ軸回転）
	float m_yaw;

	// 注視するオブジェクトの座標
	DirectX::SimpleMath::Vector3 m_targetObjectPosition;

	// 感度
	float m_sensitivity;

	// 初期回転角
	DirectX::SimpleMath::Quaternion m_initial_angle;
	// 現在の回転角
	DirectX::SimpleMath::Quaternion m_current_angle;
};