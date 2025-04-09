// ============================================
// 
// ファイル名: ScoreUI.cpp
// 概要: スコアのUI
// 
// 製作者 : 清水駿希
// 
// ============================================

#include "Framework/pch.h"
#include "Game/UI/ScoreUI.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"

#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Transform/Transform.h"

/// <summary>
/// コンストラクタ
/// </summary>
ScoreUI::ScoreUI()
	:
	m_isActive{},
	m_objectId{},
	m_transform{},
	m_image{},
	m_material{},
	m_currentScore{}
{
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="objectID">オブジェクトID</param>
/// <param name="active">アクティブ処理</param>
void ScoreUI::Initialize(ObjectID objectID, const bool& active)
{
	m_objectId = objectID;
	m_isActive = active;

	m_currentScore = 0.0f;

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
	m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetNumbers1(), width, height);
	m_image->SetRuleTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetRuleTexture());
	m_image->SetIsActive(active);

	// マテリアルを初期化する
	this->InitialMaterial(width,height);

	DirectX::SimpleMath::Vector4 digits;
	digits.x = static_cast<float>(((int)m_currentScore / 1000) % 10); // 1000の位
	digits.y = static_cast<float>(((int)m_currentScore / 100) % 10);  //  100の位
	digits.z = static_cast<float>(((int)m_currentScore / 10) % 10);   //   10の位
	digits.w = static_cast<float>((int)m_currentScore % 10);          //    1の位

	// Transformの初期化
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
	m_transform->SetRect(digits);
	m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

	commonResources->GetRenderManager()->AddSprite(m_image.get());
}

/// <summary>
/// Transformの初期化処理
/// </summary>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">大きさ</param>
void ScoreUI::InitialTransform(
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
void ScoreUI::Update()
{
}

/// <summary>
/// 終了処理
/// </summary>
void ScoreUI::Finalize()
{
}

/// <summary>
/// マテリアルの初期化
/// </summary>
/// <param name="width">テクスチャ横</param>
/// <param name="height">テクスチャ縦</param>
void ScoreUI::InitialMaterial(int width, int height)
{
	auto material = dynamic_cast<DefaultUi*>(m_material.get());

	material->SetPixelShader(CommonResources::GetInstance()->GetResources()->GetShaderResources()->GetScorePS());
	material->SetWindowSize({ 1280.0f,720.0f });
	material->SetTextureSize({ (float)width, (float)height });
	material->SetUseTexture(1.0f);
	material->SetUseRuleTexture(0.0f);
	material->SetRuleProgress(0.0f);
	material->SetRuleInverse(0.0f);
}

/// <summary>
/// スコアを追加
/// </summary>
/// <param name="score">増加量</param>
void ScoreUI::AddScore(float score)
{
	m_currentScore += score;

	DirectX::SimpleMath::Vector4 digits;
	digits.x = static_cast<float>(((int)m_currentScore / 1000) % 10); // 1000の位
	digits.y = static_cast<float>(((int)m_currentScore / 100) % 10);  //  100の位
	digits.z = static_cast<float>(((int)m_currentScore / 10) % 10);   //   10の位
	digits.w = static_cast<float>((int)m_currentScore % 10);          //    1の位

	m_transform->SetRect(digits);
}

/// <summary>
/// スコアを減算
/// </summary>
/// <param name="score">減算慮</param>
void ScoreUI::SubtractScore(float socre)
{
	m_currentScore += socre;

	DirectX::SimpleMath::Vector4 digits;
	digits.x = static_cast<float>(((int)m_currentScore / 1000) % 10); // 1000の位
	digits.y = static_cast<float>(((int)m_currentScore / 100) % 10);  //  100の位
	digits.z = static_cast<float>(((int)m_currentScore / 10) % 10);   //   10の位
	digits.w = static_cast<float>((int)m_currentScore % 10);          //    1の位

	m_transform->SetRect(digits);
}

/// <summary>
/// スコアをゼロにリセット
/// </summary>
void ScoreUI::ResetScore()
{
	m_currentScore = 0.0f;

	DirectX::SimpleMath::Vector4 digits;
	digits.x = static_cast<float>(((int)m_currentScore / 1000) % 10); // 1000の位
	digits.y = static_cast<float>(((int)m_currentScore / 100) % 10);  //  100の位
	digits.z = static_cast<float>(((int)m_currentScore / 10) % 10);   //   10の位
	digits.w = static_cast<float>((int)m_currentScore % 10);          //    1の位

	m_transform->SetRect(digits);
}


/// <summary>
/// メッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
void ScoreUI::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	switch (messageID)
	{
		case Message::ADD_SCORE_TEN:
			this->AddScore(10.0f);
			break;
		case Message::ADD_SCORE_ONE_HUNDRED:
			this->AddScore(100.0f);
			break;
		case Message::ADD_SCORE_ONE_THOUSAND:
			this->AddScore(1000.0f);
			break;
		case Message::SUBTRACT_SCORE_TEN:
			this->SubtractScore(10.0f);
			break;
		case Message::SUBTRACT_SCORE_ONE_HUNDRED:
			this->SubtractScore(100.0f);
			break;
		case Message::SUBTRACT_SCORE_ONE_THOUSAND:
			this->SubtractScore(1000.0f);
			break;
		case Message::RESET_SCORE:
			this->ResetScore();
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
void ScoreUI::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}