// ============================================
// 
// ファイル名: CameraManager.cpp
// 概要: カメラを管理するクラス（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================

#include "Framework/pch.h"
#include "Framework/CameraManager.h"
#include "Framework/CommonResources.h"
#include "Interface/ICamera.h"
#include "Game/Transform/Transform.h"
#include "Framework/Tween/Tween.h"

/// <summary>
/// コンストラクタ
/// </summary>
CameraManager::CameraManager()
	:
	m_cameraIndex{},
	m_cameras{},
	m_pendingCameras{},
	m_viewMatrix{},
	m_projectionMatrix{},
	m_isFadeActive{},
	m_transform{}
{
	// 初期化
	m_cameraIndex  = 0;
	m_isFadeActive = false;
	// Transformの作成
	m_transform = std::make_unique<Transform>();

	// プロジェクション行列作成
	m_projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		DirectX::XMConvertToRadians(60.0f),
		SCREEN_W / SCREEN_H,
		0.1f,
		100000.0f
	);
}


/// <summary>
/// カメラを追加する
/// </summary>
/// <param name="camera">追加するカメラ</param>
ICamera* CameraManager::Attach(std::unique_ptr<ICamera> camera)
{
	// カメラを追加する
	m_pendingCameras.push_back(std::move(camera));

	// 現在のカメラを設定を行うため返す
	return camera.get();

}
/// <summary>
/// 更新処理
/// </summary>
void CameraManager::Update()
{
	// カメラを切り替える処理
	this->Fade();

	// カメラを切り替えている時はカメラの更新をストップ
	if (m_isFadeActive) return;

	// カメラの更新処理
	if (m_cameraIndex != -1)
	{
		m_cameras[m_cameraIndex]->Update();
		// ビュー行列を作成
		//m_viewMatrix = m_cameras[m_cameraIndex]->CalculateViewMatrix();
		m_viewMatrix = m_cameras[m_cameraIndex]->GetViewMatrix();
	}
}

void CameraManager::Detach()
{

}

/// <summary>
/// 全てのカメラを準備段階のものに切り替える
/// </summary>
void CameraManager::SwitchCameras()
{
	// 現在のカメラを削除
	m_cameras.clear();
	// カメラを更新
	m_cameras = std::move(m_pendingCameras);
	// 準備段階の配列をクリアする
	m_pendingCameras.clear();
	// 値を初期化
	if (m_cameras.size() == 0)
		m_cameraIndex = -1;
	else
		m_cameraIndex = 0;
}

/// <summary>
/// 指定されたインデックスのカメラに切り替える
/// </summary>
/// <param name="index">切り替え先のカメラのインデックス</param>
void CameraManager::SwitchActiveCamera(int index)
{
	// カメラを切り替え中にする
	m_isFadeActive = true;

	// 現在のカメラの座標情報を保存
	m_transform->SetLocalPosition(m_cameras[m_cameraIndex]->GetTransform()->GetLocalPosition());
	// 現在のカメラのターゲットを保存
	m_transform->SetLocalScale(m_cameras[m_cameraIndex]->GetTransform()->GetLocalScale());

	// Tweenを起動
	m_transform->GetTween()->DOMove(m_cameras[index]->GetTransform()->GetLocalPosition(),0.0f);
	m_transform->GetTween()->DOScale(m_cameras[index]->GetTransform()->GetLocalScale(), 0.0f).OnComplete([this] {
		// フェードが終わったらカメラのビュー行列を作成する
		m_viewMatrix = m_cameras[m_cameraIndex]->CalculateViewMatrix();
	});

	// 次のカメラの番号を設定
	m_cameraIndex = index;
}
/// <summary>
/// 指定されたインデックスのカメラにフェード付きで切り替える
/// </summary>
/// <param name="index">切り替え先のカメラのインデックス</param>
/// <param name="fadeTime">カメラ切り替えのフェード時間（秒）</param>
/// <param name="easingType">フェードアニメーションのイージングタイプ</param>
void CameraManager::SwitchActiveCamera(int index, float fadeTime, Tween::EasingType easingType)
{
	// カメラを切り替え中にする
	m_isFadeActive = true;

	// スタート地点
	m_startPosition = m_cameras[m_cameraIndex]->GetTransform()->GetLocalPosition();
	m_endTarget = m_cameras[m_cameraIndex]->GetTransform()->GetLocalScale();
	// 終了地点
	m_endPosition = m_cameras[index]->GetTransform()->GetLocalPosition();
	m_endTarget = m_cameras[index]->GetTransform()->GetLocalScale();

	m_elapsed = 0.0f;
	m_fadeTime = fadeTime;

	// 次のカメラの番号を設定
	m_cameraIndex = index;
}

/// <summary>
/// フェード中のビュー行列を作成
/// </summary>
void CameraManager::Fade()
{
	// カメラ切り替え中出なければ更新しない
	if (!m_isFadeActive) return;

	// 経過時間の取得
	float elapsedTime = (float)CommonResources::GetInstance()->GetStepTimer()->GetElapsedSeconds();

	// 現在の時間を更新する
	m_elapsed += elapsedTime;

	// アニメーションの進行度を計算（0.0 ～ 1.0 に正規化）
	float t = (m_elapsed) / m_fadeTime;
	// t を 1.0 にクランプ（補間の上限を超えないようにする）
	if (t > 1.0f) t = 1.0f;

	// 終了地点
	m_endPosition = m_cameras[m_cameraIndex]->GetTransform()->GetLocalPosition();
	m_endTarget = m_cameras[m_cameraIndex]->GetTransform()->GetLocalScale();

	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Lerp(m_startPosition, m_endPosition, t);
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3::Lerp(m_endPosition, m_endTarget, t);

	if(t >= 1.0f)
	m_isFadeActive = false;

	// ビュー行列を更新する
	m_viewMatrix =
		DirectX::SimpleMath::Matrix::CreateLookAt(
			position, target, DirectX::SimpleMath::Vector3::Up
	);	
}