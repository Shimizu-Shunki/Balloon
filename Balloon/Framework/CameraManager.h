#pragma once
#include "Interface/ICamera.h"
#include "Framework/Tween/Tween.h"

class ICamera;
class Transform;


class CameraManager
{
private:
	const float SCREEN_W = 1280.0f;
	const float SCREEN_H = 720.0f;

public:

	// ビュー行列を取得する
	DirectX::SimpleMath::Matrix GetViewMatrix() const { return m_viewMatrix; }
	// ビュー行列を設定
	void SetViewMatrix(const DirectX::SimpleMath::Matrix& viewMatrix) { m_viewMatrix = viewMatrix; }

	// プロジェクション行列を取得する
	DirectX::SimpleMath::Matrix GetProjectionMatrix() const { return m_projectionMatrix; }
	// プロジェクション行列を設定する
	void SetProjectionMatrix(const DirectX::SimpleMath::Matrix& projectionMatirx) { m_projectionMatrix = projectionMatirx; }

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
	
	// 現在のカメラを削除し、準備済みのカメラに切り替える
	void SwitchCameras();
	// カメラの更新処理
	void Update();

	// カメラを追加
	ICamera* Attach(std::unique_ptr<ICamera> camera);
	// カメラを削除
	void Detach();

	// カメラフェード処理
	void Fade();

	// カメラを切り替える
	void SwitchActiveCamera(int index);
	void SwitchActiveCamera(int index, float fadeTime , Tween::EasingType easingType);

	

private:
	// 現在のカメラ番号
	int m_cameraIndex;

	// 管理対象のカメラリスト
	std::vector<std::unique_ptr<ICamera>> m_cameras; 
	// 準備段階のカメラリスト
	std::vector<std::unique_ptr<ICamera>> m_pendingCameras;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_viewMatrix;
	// プロジェクション行列
	DirectX::SimpleMath::Matrix m_projectionMatrix;

	// カメラを切り替え中かどうか
	bool m_isFadeActive;	
	
	// 仮想Transform（補間用）
	std::unique_ptr<Transform> m_transform;	
};