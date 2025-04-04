#include "Framework/pch.h"
#include "Game/UI/ScoreUI.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"

#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Transform/Transform.h"


ScoreUI::ScoreUI()
{
}


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
	digits.x = ((int)m_currentScore / 1000) % 10; // 1000の位
	digits.y = ((int)m_currentScore / 100) % 10; // 100の位
	digits.z = ((int)m_currentScore / 10) % 10; //  10の位
	digits.w = (int)m_currentScore % 10; //   1の位

	// Transformの初期化
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
	m_transform->SetRect(digits);
	m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

	commonResources->GetRenderManager()->AddSprite(m_image.get());
}

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


void ScoreUI::Finalize()
{
}


void ScoreUI::Update()
{
}

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


void ScoreUI::AddScore(float score)
{
	m_currentScore += score;

	DirectX::SimpleMath::Vector4 digits;
	digits.x = ((int)m_currentScore / 1000) % 10; // 1000の位
	digits.y = ((int)m_currentScore / 100) % 10; // 100の位
	digits.z = ((int)m_currentScore / 10) % 10; //  10の位
	digits.w = (int)m_currentScore % 10; //   1の位

	m_transform->SetRect(digits);
}

void ScoreUI::SubtractScore(float socre)
{
	m_currentScore += socre;

	DirectX::SimpleMath::Vector4 digits;
	digits.x = ((int)m_currentScore / 1000) % 10; // 1000の位
	digits.y = ((int)m_currentScore / 100) % 10; // 100の位
	digits.z = ((int)m_currentScore / 10) % 10; //  10の位
	digits.w = (int)m_currentScore % 10; //   1の位

	m_transform->SetRect(digits);
}

void ScoreUI::ResetScore()
{
	m_currentScore = 0.0f;

	DirectX::SimpleMath::Vector4 digits;
	digits.x = ((int)m_currentScore / 1000) % 10; // 1000の位
	digits.y = ((int)m_currentScore / 100) % 10; // 100の位
	digits.z = ((int)m_currentScore / 10) % 10; //  10の位
	digits.w = (int)m_currentScore % 10; //   1の位

	m_transform->SetRect(digits);
}



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
		case Message::SUBTRACT_ONE_HUNDRED:
			this->SubtractScore(100.0f);
			break;
		case Message::SUBTRACT_ONE_THOUSAND:
			this->SubtractScore(1000.0f);
			break;
		case Message::RESET_SCORE:
			this->ResetScore();
			break;
		default:
			break;
	}
}

void ScoreUI::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}