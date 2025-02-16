#include "Framework/pch.h"
#include "Framework/RenderManager.h"
#include "Framework/CommonResources.h"
#include "Framework/CameraManager.h"
#include "Game/Transform/Transform.h"

RenderManager::RenderManager()
	:
	m_sprite{},
	m_pendingSprite{},
	m_skySphere{},
	m_renderableObjects{},
	m_pendingRenderableObjects{}
{
	// 共有リソース
	auto commonResources = CommonResources::GetInstance();
	// デバイス
	m_device = commonResources->GetDeviceResources()->GetD3DDevice();
	// コンテキスト
	m_context = commonResources->GetDeviceResources()->GetD3DDeviceContext();
	// コモンステート
	m_commonStates = commonResources->GetCommonStates();
	// カメラ管理クラス
	m_cameraManager = commonResources->GetCameraManager();
}


void RenderManager::SwitchRenderbleObjects()
{
	// 現在のオブジェクトを削除する
	m_renderableObjects.clear();
	// 次のオブジェクトを格納する
	m_renderableObjects = m_pendingRenderableObjects;

	// 現在のスプライトを削除する
	m_sprite.clear();
	// 次のスプライトを格納する
	m_sprite = m_pendingSprite;

	m_pendingSprite.clear();
	m_pendingRenderableObjects.clear();
}

void RenderManager::Render()
{
	// スカイスフィアを描画する スカイスフィアがない場合エラー処理を行い描画を行わない
	if (!m_skySphere.model) {
		throw std::runtime_error("m_skySphere.model is nullptr!");
	}

	// プロジェクション行列を取得する
	const DirectX::SimpleMath::Matrix& projectionMatrix = m_cameraManager->GetProjectionMatrix();
	// ビュー行列を取得する
	const DirectX::SimpleMath::Matrix& viewMatrix       = m_cameraManager->GetViewMatrix();


	// モデルのエフェクト情報を更新する
	m_skySphere.model->UpdateEffects([](DirectX::IEffect* effect)
	{
		// ベーシックエフェクトを設定する
		DirectX::DX11::BasicEffect* basicEffect = dynamic_cast<DirectX::DX11::BasicEffect*>(effect);
		if (basicEffect)
		{
			// 個別のライトをすべて無効化する
			basicEffect->SetLightEnabled(0, false);
			basicEffect->SetLightEnabled(1, false);
			basicEffect->SetLightEnabled(2, false);

			// モデルを自発光させる
			basicEffect->SetEmissiveColor(DirectX::Colors::White);
		}
	});
	// スカイスフィアを描画する
	m_skySphere.model->Draw(m_context, *m_commonStates, m_skySphere.transform->GetWorldMatrix(),
		viewMatrix, projectionMatrix);


	// モデルの描画
	for (const auto& model : m_renderableObjects)
	{
		if(model.model != nullptr)
		model.model->Draw(m_context, *m_commonStates, model.transform->GetWorldMatrix(),
			viewMatrix, projectionMatrix
		);
	}

	// スプライトの描画
	for (const auto& sprite : m_sprite)
	{
		if (sprite != nullptr)
		{
			// マテリアルの適応
			sprite->Begin();
			// 描画
			m_context->Draw(1, 0);
			// マテリアルの解放
			sprite->End();
		}
	}
}