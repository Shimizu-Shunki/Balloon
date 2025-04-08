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

StageNumberUI::StageNumberUI(StageNumberID stageNumberId)
{
	m_stageNumberId = stageNumberId;
}


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

	// マテリアルを初期化する
	this->InitialMaterial(TEXTURE_WIDTH, TEXTURE_HEIGHT);

	// Transformの初期化
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
	m_transform->SetRect({ 0.0f , (stageNumberHeight - TEXTURE_HEIGHT) / 9.0f , TEXTURE_WIDTH , stageNumberHeight / 9.0f});
	m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

	commonResources->GetRenderManager()->AddSprite(m_image.get());
}

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


void StageNumberUI::Finalize()
{

}


void StageNumberUI::Update()
{
	//m_material->UpdateConstBuffer();
}

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

void StageNumberUI::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	(void)messageID;
}

void StageNumberUI::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}