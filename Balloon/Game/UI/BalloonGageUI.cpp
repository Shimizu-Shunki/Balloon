// ============================================
// 
// ファイル名: BalloonGageUI.cpp
// 概要: 風船のゲージUI
// 
// 製作者 : 清水駿希
// 
// ============================================

#include "Framework/pch.h"
#include "Game/UI/BalloonGageUI.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"
#include "Game/Message/ObjectMessenger.h"

#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Transform/Transform.h"

const float BalloonGageUI::SPEED_SLOW = 0.7f;
const float BalloonGageUI::SPEED_NORMAL = 0.5f;
const float BalloonGageUI::SPEED_FAST = 0.3f;

/// <summary>
/// コンストラクタ
/// </summary>
BalloonGageUI::BalloonGageUI()
	:
	m_isActive{},
	m_objectId{},
	m_transform{},
	m_image{},
	m_material{},
	m_currentScale{},
	m_isBalloon{},
	m_speed{}
{
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="objectID">オブジェクトID</param>
/// <param name="active">アクティブ状態</param>
void BalloonGageUI::Initialize(ObjectID objectID, const bool& active)
{
	m_objectId = objectID;
	m_isActive = active;

	m_currentScale = 0.0f;
	m_isBalloon = false;

	m_speed = SPEED_NORMAL;

	// 共有リソース
	auto commonResources = CommonResources::GetInstance();
	int width, height;

	// Transformの作成
	m_transform = std::make_unique<Transform>();
	// Imageの作成
	m_image = std::make_unique<Image>();
	// Materialの作成
	m_material = std::make_unique<DefaultUi>();

	// Imageの初期化
	m_image->Initialize(active, m_material.get(), m_transform.get());
	m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetBalloonGage(), width, height);
	m_image->SetRuleTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetRuleTexture());
	m_image->SetIsActive(active);

	// マテリアルを初期化する
	this->InitialMaterial(width,height);

	// Transformの初期化
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
	m_transform->SetRect({ 0.0f,0.0f,(float)width,(float)height});
	m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

	commonResources->GetRenderManager()->AddSprite(m_image.get());
}

/// <summary>
/// Transformの初期化
/// </summary>
/// <param name="position">位置</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
void BalloonGageUI::InitialTransform(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	m_transform->SetLocalPosition(position);
	m_transform->SetLocalRotation(rotation);
	m_transform->SetLocalScale(scale);
}

/// <summary>
/// 更新処理
/// </summary>
void BalloonGageUI::Update()
{
	float elapsedTime = (float)CommonResources::GetInstance()->GetStepTimer()->GetElapsedSeconds();

	// オンの場合
	if (m_isBalloon)
	{
		m_currentScale += elapsedTime * m_speed;

		if (m_currentScale >= 1.0f)
		{
			m_currentScale = 1.0f;
		}
	}
	else
	{
		m_currentScale -= elapsedTime * m_speed;

		if (m_currentScale <= 0.0f)
		{
			m_currentScale = 0.0f;
		}
	}

	// 位置を補間
	m_transform->SetLocalPosition({
		m_transform->GetLocalPosition().x,
		600.0f + 33.0f * (std::abs(m_currentScale - 1.0f)),
		0.0f
		});
	// 大きさを設定
	float scaled = 0.1f + (m_currentScale * (0.6f - 0.1f));
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One * scaled);

}

/// <summary>
/// 終了処理
/// </summary>
void BalloonGageUI::Finalize()
{

}

/// <summary>
/// マテリアルの初期化
/// </summary>
/// <param name="width">テクスチャ横</param>
/// <param name="height">テクスチャ縦</param>
void BalloonGageUI::InitialMaterial(int width, int height)
{
	auto material = dynamic_cast<DefaultUi*>(m_material.get());

	material->SetPixelShader(CommonResources::GetInstance()->GetResources()->GetShaderResources()->GetUI_PS());
	material->SetWindowSize({ 1280.0f,720.0f });
	material->SetTextureSize({ (float)width, (float)height });
	material->SetUseTexture(1.0f);
	material->SetUseRuleTexture(0.0f);
	material->SetRuleProgress(0.0f);
	material->SetRuleInverse(0.0f);
}

/// <summary>
/// メッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
void BalloonGageUI::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	switch (messageID)
	{
		case Message::ON_BALLOON:
			m_isBalloon = true;

			for (int i = 0; i < 3; i++)
				ObjectMessenger::GetInstance()->Dispatch(i + 4, Message::ObjectMessageID::ON_BALLOON);

			break;
		case Message::OFF_BALLOON:
			m_isBalloon = false;

			for (int i = 0; i < 3; i++)
				ObjectMessenger::GetInstance()->Dispatch(i + 4, Message::ObjectMessageID::OFF_BALLOON);
			break;
		case Message::BALLOON_SPEED_SLOW:
			m_speed = SPEED_SLOW;
			break;
		case Message::BALLOON_SPEED_NORMAL:
			m_speed = SPEED_NORMAL;
			break;
		case Message::BALLOON_SPEED_FAST:
			m_speed = SPEED_FAST;
			break;
		default:
			break;
	}
}

/// <summary>
/// 当たり判定のメッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
/// <param name="sender">当たった相手のオブジェクト</param>
void BalloonGageUI::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}