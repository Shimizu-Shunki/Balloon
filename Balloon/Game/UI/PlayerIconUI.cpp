#include "Framework/pch.h"
#include "Game/UI/PlayerIconUI.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"

#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Transform/Transform.h"


PlayerIconUI::PlayerIconUI(Transform* player)
{
	
	m_playerTransform = player;
}


void PlayerIconUI::Initialize(ObjectID objectID, const bool& active)
{
	m_objectId = objectID;
	m_isActive = active;

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
	m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetPlayerIcon(), width, height);
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

void PlayerIconUI::InitialTransform(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	m_transform->SetLocalPosition(position);
	m_transform->SetLocalRotation(rotation);
	m_transform->SetLocalScale(scale);
}


void PlayerIconUI::Finalize()
{

}


void PlayerIconUI::Update()
{
	//m_material->UpdateConstBuffer();

	// プレイヤーの高さを正規化
	float height = std::clamp(m_playerTransform->GetLocalPosition().y / 5.0f, -1.0f, 1.0f);

	height *= -1.0f;

	height = 360.0f + (140.0f * height);

	// アイコンの高さを設定
	m_transform->SetLocalPosition({ m_transform->GetLocalPosition().x , height , m_transform->GetLocalPosition().z });
}

void PlayerIconUI::InitialMaterial(int width, int height)
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

float PlayerIconUI::GetNormalizedHeight(float height)
{
	float value = (-height + 5.0f) / 10.0f;
	return std::clamp(value, 0.0f, 1.0f);
}

void PlayerIconUI::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	(void)messageID;
}

void PlayerIconUI::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}