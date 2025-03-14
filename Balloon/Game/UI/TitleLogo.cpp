#include "Framework/pch.h"
#include "Game/UI/TitleLogo.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"

#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Transform/Transform.h"


TitleLogo::TitleLogo()
{
	

}


void TitleLogo::Initialize(ObjectID objectID, const bool& active)
{
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
	m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetTitleLogo(), width, height);
	m_image->SetRuleTexture(nullptr);
	m_image->SetIsActive(true);

	// マテリアルを初期化する
	this->InitialMaterial(width,height);

	// Transformの初期化
	m_transform->SetLocalPosition({ 365.7f , 240.0f , 0.0f });
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetRect({ 0.0f,0.0f,(float)width,(float)height});
	m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

	// タイトルロゴのアニメーションを設定
	m_transform->GetTween()->DOScale(DirectX::SimpleMath::Vector3::One * 0.5f, 1.0f)
		.SetDelay(4.0f).SetEase(Tween::EasingType::EaseOutBounce);

	commonResources->GetRenderManager()->AddSprite(m_image.get());
}

void TitleLogo::InitialTransform(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{

}


void TitleLogo::Finalize()
{

}


void TitleLogo::Update()
{
	//m_material->UpdateConstBuffer();
}

void TitleLogo::InitialMaterial(int width, int height)
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