#include "Framework/pch.h"
#include "Game/Sky/SkySphere.h"
#include "Framework/CommonResources.h"
#include "Game/Transform/Transform.h"

// 砲塔スピード
const float SkySphere::ROTATION_SPEED = 1.5f;

/// <summary>
/// コンストラクタ
/// </summary>
SkySphere::SkySphere()
	:
	m_model{},
	m_transform{}
{
	// インスタンスを取得する
	m_commonResources = CommonResources::GetInstance();
}


/// <summary>
/// 初期化処理
/// </summary>
void SkySphere::Initialize()
{
	// コンテキスト
	m_context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// モデルを取得する 「スカイスフィア」
	m_model = m_commonResources->GetResources()->GetSkySphere();
	// Transformを作成する
	m_transform = std::make_unique<Transform>();

	// 親はなし
	m_transform->SetParent(nullptr);

	// 座標初期化
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Up * 250.0f);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale({ 5.0f, 3.5f, 5.0f });

	// スカイスフィアをRenderManagerに登録する
	m_commonResources->GetRenderManager()->SetSkySphereObject({ m_transform.get(),m_model });
}

/// <summary>
/// 更新処理
/// </summary>
void SkySphere::Update()
{
	// フレーム
	float elapsedTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	// Y軸に回転
	m_transform->SetLocalRotation(
		m_transform->GetLocalRotation() *
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3::Up, DirectX::XMConvertToRadians(ROTATION_SPEED * elapsedTime))
	);

	// Transform更新
	m_transform->Update();
}

