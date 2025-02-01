#pragma once
#include "Interface/ICamera.h"

class CommonResources;
class ICamera;


class CameraManager
{
public:

	// ビュー行列を取得する
	DirectX::SimpleMath::Matrix GetViewMatrix() const { return m_viewMatrix; }
	// ビュー行列を設定
	void SetViewMatrix(DirectX::SimpleMath::Matrix viewMatrix) { m_viewMatrix = viewMatrix; }

private:
	//	コンストラクタ
	CameraManager();
	//	デストラクタ
	~CameraManager() = default;

public:
	CameraManager(const CameraManager&) = delete;             // コピー禁止
	CameraManager& operator=(const CameraManager&) = delete;  // コピー代入禁止
	CameraManager(const CameraManager&&) = delete;            // ムーブ禁止
	CameraManager& operator=(const CameraManager&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static CameraManager* GetInstance()
	{
		static CameraManager instance;
		return &instance;
	}

public:
	// カメラの更新処理
	void Update(const float& deltaTime);

	// カメラを追加
	void Attach(std::unique_ptr<ICamera> camera);
	// カメラを削除
	void Detach();

	// カメラフェード処理
	void Fade(const float& deltaTime);

	// カメラを切り替える
	void ChageCamera(int index);

private:
	// グラフィック
	CommonResources* m_commonResources;

	// 管理対象のカメラリスト
	std::vector<std::unique_ptr<ICamera>> m_cameras; 

	// 現在のカメラ番号
	int m_cameraIndex;

	// カメラを切り替え中かどうか
	bool m_isFadeActive;

	// 現在のカメラの座標
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// 現在のカメラのターゲット座標
	DirectX::SimpleMath::Vector3 m_currentTargetPosition;
	// 次のカメラの座標
	DirectX::SimpleMath::Vector3 m_nextPosition;
	// 次のカメラのターゲット座標
	DirectX::SimpleMath::Vector3 m_nextTargetPosition;

	// フェード時間
	float m_fadeTime;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_viewMatrix;


};