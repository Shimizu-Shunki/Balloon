#include "Framework/pch.h"
#include "Framework/CameraManager.h"
#include "Framework/CommonResources.h"
#include "Interface/ICamera.h"

CameraManager::CameraManager()
{
	m_commonResources = CommonResources::GetInstance();
	m_cameraIndex = 0;
	m_isFadeActive = false;
	m_fadeTime = 0.0f;
}



void CameraManager::Attach(std::unique_ptr<ICamera> camera)
{
	// カメラを追加する
	m_cameras.push_back(std::move(camera));
}

void CameraManager::Update(const float& deltaTime)
{
	// カメラを切り替える処理
	this->Fade(deltaTime);

	// カメラを切り替えている時はカメラの更新をストップ
	if (m_isFadeActive) return;

	// カメラの更新処理
	m_cameras[m_cameraIndex]->Update(deltaTime);
	// ビュー行列を作成
	m_viewMatrix = m_cameras[m_cameraIndex]->CalculateViewMatrix();
}

void CameraManager::Detach()
{

}

void CameraManager::ChageCamera(int index)
{
	// カメラを切り替え中にする
	m_isFadeActive = true;

	// 現在のカメラの座標情報を保存
	m_currentPosition = m_cameras[m_cameraIndex]->GetPosition();
	// 現在のカメラのターゲット座標情報を保存
	m_currentTargetPosition = m_cameras[m_cameraIndex]->GetTargetPosition();

	// 次のカメラの座標情報を保存
	m_nextPosition = m_cameras[index]->GetPosition();
	// 次のカメラのターゲット座標情報を保存
	m_nextTargetPosition = m_cameras[index]->GetTargetPosition();

	// 次のカメラの番号を設定
	m_cameraIndex = index;
	// フェードタイムをリセット
	m_fadeTime = 0.0f;
}

void CameraManager::Fade(const float& deltaTime)
{
	// カメラ切り替え中出なければ更新しない
	if (!m_isFadeActive) return;

	// フェード時間を更新する
	m_fadeTime += deltaTime;

	// 現在のカメラと次のカメラを補間する
	DirectX::SimpleMath::Vector3 resultPosition = 
		DirectX::SimpleMath::Vector3::Lerp(m_currentPosition, m_nextPosition,m_fadeTime);
	// 現在のターゲットと次のターゲットを補間する
	DirectX::SimpleMath::Vector3 resultTargetPosition =
		DirectX::SimpleMath::Vector3::Lerp(m_currentTargetPosition, m_nextTargetPosition, m_fadeTime);

	// ビュー行列を更新する
	m_viewMatrix =
		DirectX::SimpleMath::Matrix::CreateLookAt(
			resultPosition, resultTargetPosition, DirectX::SimpleMath::Vector3::Up
	);

	if (m_fadeTime <= 1.0f) return;

	// フェードし終わったら非アクティブにする
	m_isFadeActive = false;
	// フェードが終わったらカメラのビュー行列を作成する
	m_viewMatrix = m_cameras[m_cameraIndex]->CalculateViewMatrix();


}