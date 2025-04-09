// ============================================
// 
// ファイル名: HPGageUI.cpp
// 概要: HPのゲージUI
// 
// 製作者 : 清水駿希
// 
// ============================================

#include "Framework/pch.h"
#include "Game/UI/HPGageUI.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"

#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Transform/Transform.h"

const float HPGageUI::SPEED_SLOW   = 0.04f;
const float HPGageUI::SPEED_NORMAL = 0.06f;
const float HPGageUI::SPEED_FAST   = 0.1f;

const float HPGageUI::RECOVERY_DELAY = 2.0f;
const float HPGageUI::HP_OFFSET_FACTOR = 147.0f;

/// <summary>
/// コンストラクタ
/// </summary>
HPGageUI::HPGageUI()
	:
	m_isActive{},
	m_objectId{},
	m_transform{},
	m_image{},
	m_material{},
	m_speed{},
	m_isHealing{},
	m_currentTime{},
	m_height{},
	m_width{},
	m_baseX{},
	m_hpOffsetFactor{}
{
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="objectID">オブジェクトID</param>
/// <param name="active">アクティブ状態</param>
void HPGageUI::Initialize(ObjectID objectID, const bool& active)
{
	m_objectId = objectID;
	m_isActive = active;

	// 初期スピードはノーマル
	m_speed = SPEED_NORMAL;

	m_currentHp = 1.0f;
	m_currentTime = 0.0f;
	m_isHealing = true;

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
	m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetHPGage(), width, height);
	m_image->SetRuleTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetRuleTexture());
	m_image->SetIsActive(active);

	// マテリアルを初期化する
	this->InitialMaterial(width,height);

	m_height = (float)height;
	m_width  = (float)width;

	float currentHpWidth = m_currentHp * m_width;

	// Transformの初期化
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
	m_transform->SetRect({ 0.0f,0.0f,currentHpWidth,(float)height});
	m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

	commonResources->GetRenderManager()->AddSprite(m_image.get());
}

/// <summary>
/// Transformの初期化
/// </summary>
/// <param name="position">位置</param>
/// <param name="rotation">回転</param>
/// <param name="scale">スケール</param>
void HPGageUI::InitialTransform(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	m_transform->SetLocalPosition(position);
	m_transform->SetLocalRotation(rotation);
	m_transform->SetLocalScale(scale);

	// 初期位置を保存
	m_baseX = position.x;
}

/// <summary>
/// マテリアルの初期化
/// </summary>
/// <param name="width">テクスチャ横</param>
/// <param name="height">テクスチャ縦</param>
void HPGageUI::InitialMaterial(int width, int height)
{
	(void)width;

	float original = m_currentHp * 535.0f;

	auto material = dynamic_cast<DefaultUi*>(m_material.get());

	material->SetPixelShader(CommonResources::GetInstance()->GetResources()->GetShaderResources()->GetUI_PS());
	material->SetWindowSize({ 1280.0f,720.0f });
	material->SetTextureSize({ original, (float)height });
	material->SetUseTexture(1.0f);
	material->SetUseRuleTexture(0.0f);
	material->SetRuleProgress(0.0f);
	material->SetRuleInverse(0.0f);
}

/// <summary>
/// 更新処理
/// </summary>
void HPGageUI::Update()
{
	// 経過時間の取得
	float elapsedTime = (float)CommonResources::GetInstance()->GetStepTimer()->GetElapsedSeconds();

	// HP回復処理
	this->UpdateHpRecovery(elapsedTime);
	// HPゲージの見た目を更新する
	this->UpdateHpGaugeVisual();
}

/// <summary>
/// 終了処理
/// </summary>
void HPGageUI::Finalize()
{

}

/// <summary>
/// HPゲージの見た目を更新する
/// </summary>
void HPGageUI::UpdateHpGaugeVisual()
{
	// HPゲージの現在幅を計算
	float currentHpWidth = m_currentHp * m_width;

	// HPゲージの位置調整
	float xOffset = m_baseX - (HP_OFFSET_FACTOR * std::abs(m_currentHp - 1.0f));

	m_transform->SetLocalPosition({
	   xOffset,
	   m_transform->GetLocalPosition().y,
	   0.0f
	});

	// HPゲージの矩形サイズを更新
	m_transform->SetRect({ 0.0f, 0.0f, currentHpWidth, m_height });

	// テクスチャサイズの更新
	auto material = dynamic_cast<DefaultUi*>(m_material.get());
	material->SetTextureSize({ currentHpWidth, m_height });
	material->UpdateConstBuffer();
}

/// <summary>
/// HP回復処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void HPGageUI::UpdateHpRecovery(float elapsedTime)
{
	// 回復処理
	if (m_isHealing)
	{
		// 回復速度に応じてHPを加算
		m_currentHp += elapsedTime * m_speed;

		// HPの上限は1.0に制限
		if (m_currentHp >= 1.0f)
			m_currentHp = 1.0f;
	}
	else
	{
		// 非回復時はタイマーを進める
		m_currentTime += elapsedTime;

		// 一定時間経過後に回復を開始

		// 2秒たったら回復中にする
		if (m_currentTime >= RECOVERY_DELAY)
		{
			m_currentTime = 0.0f;
			m_isHealing = true;
		}
	}
}

/// <summary>
/// メッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
void HPGageUI::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	switch (messageID)
	{
	// HPを0.1減らす
	case Message::SUBTRACT_HP01:
		m_currentHp -= 0.1f;
		break;
	// HPを0.05減らす
	case Message::SUBTRACT_HP005:
		m_currentHp -= 0.05f;
		break;
	// 回復速度を遅く設定
	case Message::RECOVERY_SPEED_SLOW:
		m_speed = SPEED_SLOW;
		break;
	// 回復速度を通常に設定
	case Message::RECOVERY_SPEED_NORMAL:
		m_speed = SPEED_NORMAL;
		break;
	// 回復速度を通常に設定
	case Message::RECOVERY_SPEED_FAST:
		m_speed = SPEED_FAST;
		break;
	default:
		break;
	}
}

/// <summary>
/// メッセージを受け取る（当たり判定）
/// </summary>
/// <param name="messageID">メッセージID</param>
void HPGageUI::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}