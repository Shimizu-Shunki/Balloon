// ============================================
// 
// ファイル名: StageNumberUI.cpp
// 概要: ステージの番号UI
// 
// 製作者 : 清水駿希
// 
// ============================================

#include "Framework/pch.h"
#include "Game/UI/StageNumberUI.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"

#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Transform/Transform.h"

const float StageNumberUI::TEXTURE_HEIGHT = 151.4f;
const float StageNumberUI::TEXTURE_WIDTH = 564.0f;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="stageNumberId">ステージ番号ID</param>
StageNumberUI::StageNumberUI(StageNumberID stageNumberId)
	:
	m_isActive{},
	m_objectId{},
	m_transform{},
	m_image{},
	m_material{},
	m_stageNumberId{}
{
	m_stageNumberId = stageNumberId;
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="objectID">オブジェクトID</param>
/// <param name="active">アクティブ処理</param>
void StageNumberUI::Initialize(ObjectID objectID, const bool& active)
{
	m_objectId = objectID;
	m_isActive = active;

	// ステージ番号のテクスチャの高さを設定
	float stageNumberHeight = 0.0f;

	stageNumberHeight = TEXTURE_HEIGHT + (TEXTURE_HEIGHT * (int)m_stageNumberId);

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
	m_image->Initialize(true, m_material.get(), m_transform.get());
	m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetStageSelectTexts(), width, height);
	m_image->SetRuleTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetRuleTexture());
	m_image->SetIsActive(active);

	
	this->InitialMaterial((int)TEXTURE_WIDTH, (int)TEXTURE_HEIGHT);

	// Transformの初期化
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
	m_transform->SetRect({ 0.0f , (stageNumberHeight - TEXTURE_HEIGHT) / 9.0f , TEXTURE_WIDTH , stageNumberHeight / 9.0f});
	m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

	commonResources->GetRenderManager()->AddSprite(m_image.get());
}

/// <summary>
/// Transformの初期化処理
/// </summary>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
/// <param name="scale">大きさ</param>
void StageNumberUI::InitialTransform(
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
void StageNumberUI::Update()
{
	//m_material->UpdateConstBuffer();
}


/// <summary>
/// 終了処理
/// </summary>
void StageNumberUI::Finalize()
{

}


/// <summary>
/// マテリアルの初期化
/// </summary>
/// <param name="width">テクスチャ横</param>
/// <param name="height">テクスチャ縦</param>
void StageNumberUI::InitialMaterial(int width, int height)
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
void StageNumberUI::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	(void)messageID;
}

/// <summary>
/// 当たり判定のメッセージを受け取る
/// </summary>
/// <param name="messageID">メッセージID</param>
/// <param name="sender">当たった相手のオブジェクト</param>
void StageNumberUI::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}