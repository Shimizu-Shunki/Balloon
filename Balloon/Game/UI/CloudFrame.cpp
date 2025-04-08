#include "Framework/pch.h"
#include "Game/UI/CloudFrame.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"

#include "Game/UI/StageNumberUI.h"

#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Transform/Transform.h"


CloudFrame::CloudFrame(int stageNumber)
{
	m_stageNumber = stageNumber;
}


void CloudFrame::Initialize(ObjectID objectID, const bool& active)
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
	m_image->Initialize(true, m_material.get(), m_transform.get());
	m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetCloudFrame(), width, height);
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

	// ステージ番号を設定
	m_stageNumberText = std::make_unique<StageNumberUI>((StageNumberUI::StageNumberID)m_stageNumber);
	m_stageNumberText->Initialize(IObject::ObjectID::STAGE_NUMBER, true);
	
}

void CloudFrame::InitialTransform(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	m_transform->SetLocalPosition(position);
	m_transform->SetLocalRotation(rotation);
	m_transform->SetLocalScale(scale);

	m_stageNumberText->InitialTransform(
		{ position.x , position.y - 180.0f , position.z },
		rotation,
		{scale.x + 0.2f , scale.y - 0.2f , scale.z }
	);
}


void CloudFrame::Finalize()
{

}


void CloudFrame::Update()
{
	//m_material->UpdateConstBuffer();

	m_stageNumberText->Update();
	m_stageNumberText->GetTransform()->Update();

}

void CloudFrame::InitialMaterial(int width, int height)
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

void CloudFrame::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	(void)messageID;
}

void CloudFrame::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}