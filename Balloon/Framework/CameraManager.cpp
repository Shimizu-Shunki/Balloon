#include "Framework/pch.h"
#include "Framework/CameraManager.h"
#include "Framework/CommonResources.h"
#include "Interface/ICamera.h"
#include "Game/Transform/Transform.h"
#include "Framework/Tween/Tween.h"

CameraManager::CameraManager()
{
	m_commonResources = CommonResources::GetInstance();
	m_cameraIndex = 0;
	m_isFadeActive = false;
	m_fadeTime = 0.0f;

	m_transform = std::make_unique<Transform>();

}



void CameraManager::Attach(std::unique_ptr<ICamera> camera)
{
	// カメラを追加する
	m_cameras.push_back(std::move(camera));
}

void CameraManager::Update()
{
	// カメラを切り替える処理
	this->Fade();

	// カメラを切り替えている時はカメラの更新をストップ
	if (m_isFadeActive) return;

	// カメラの更新処理
	//if (m_cameras[m_cameraIndex] != nullptr)
	//{
	//	m_cameras[m_cameraIndex]->Update();
	//	// ビュー行列を作成
	//	m_viewMatrix = m_cameras[m_cameraIndex]->CalculateViewMatrix();
	//}
}

void CameraManager::Detach()
{

}

void CameraManager::ChageCamera(int index)
{
	// カメラを切り替え中にする
	m_isFadeActive = true;

	// 現在のカメラの座標情報を保存
	m_transform->SetLocalPosition(m_cameras[m_cameraIndex]->GetTransform()->GetLocalPosition());
	// 現在のカメラのターゲットを保存
	m_transform->SetLocalScale(m_cameras[m_cameraIndex]->GetTransform()->GetLocalScale());

	// Tweenを起動
	m_transform->GetTween()->DOMove(m_cameras[index]->GetTransform()->GetLocalPosition(), 2.0f);
	m_transform->GetTween()->DOScale(m_cameras[index]->GetTransform()->GetLocalScale(), 2.0f).OnComplete([this] {
		// フェードが終わったらカメラのビュー行列を作成する
		m_viewMatrix = m_cameras[m_cameraIndex]->CalculateViewMatrix();
	});

	// 次のカメラの番号を設定
	m_cameraIndex = index;
	// フェードタイムをリセット
	m_fadeTime = 0.0f;
}

void CameraManager::Fade()
{
	// カメラ切り替え中出なければ更新しない
	if (!m_isFadeActive) return;

	// ビュー行列を更新する
	m_viewMatrix =
		DirectX::SimpleMath::Matrix::CreateLookAt(
			m_transform->GetLocalPosition(), m_transform->GetLocalScale(), DirectX::SimpleMath::Vector3::Up
	);	

	m_commonResources->GetCameraManager()->SetViewMatrix(m_viewMatrix);
}