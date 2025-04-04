#include "Framework/pch.h"
#include "Game/UI/TimerUI.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"

#include "Game/Image/Image.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Transform/Transform.h"


TimerUI::TimerUI(bool isCountingUp, float currentTime)
{
	m_isCountingUp = isCountingUp;
	m_currentTime = currentTime;
}


void TimerUI::Initialize(ObjectID objectID, const bool& active)
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
	m_image->SetTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetNumbers(), width, height);
	m_image->SetRuleTexture(CommonResources::GetInstance()->GetResources()->GetTextureResources()->GetRuleTexture());
	m_image->SetIsActive(active);

	// マテリアルを初期化する
	this->InitialMaterial(width,height);

	// 分と秒を計算
	int minutes = static_cast<int>(m_currentTime) / 60;
	int seconds = static_cast<int>(m_currentTime) % 60;

	// 各桁を計算 (例: 23:45 -> {2, 3, 4, 5})
	DirectX::SimpleMath::Vector4 digits;
	digits.x = minutes / 10; // 分の10の位
	digits.y = minutes % 10; // 分の1の位
	digits.z = seconds / 10; // 秒の10の位
	digits.w = seconds % 10; // 秒の1の位

	// Transformの初期化
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
	m_transform->SetRect(digits);
	m_transform->SetColor(DirectX::SimpleMath::Vector4::One);

	commonResources->GetRenderManager()->AddSprite(m_image.get());
}

void TimerUI::InitialTransform(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	m_transform->SetLocalPosition(position);
	m_transform->SetLocalRotation(rotation);
	m_transform->SetLocalScale(scale);
}


void TimerUI::Finalize()
{

}


void TimerUI::Update()
{
	float elapsedTime = (float)CommonResources::GetInstance()->GetStepTimer()->GetElapsedSeconds();

	if (m_isCountingUp)
	{
		m_currentTime += elapsedTime;
	}
	else
	{
		if (m_currentTime > 0.0f)
		{
			m_currentTime -= elapsedTime;
		}
		else
		{
			m_currentTime = 0.0f;
		}
	}

	// 分と秒を計算
	int minutes = static_cast<int>(m_currentTime) / 60;
	int seconds = static_cast<int>(m_currentTime) % 60;

	// 各桁を計算 (例: 23:45 -> {2, 3, 4, 5})
	DirectX::SimpleMath::Vector4 digits;
	digits.x = minutes / 10; // 分の10の位
	digits.y = minutes % 10; // 分の1の位
	digits.z = seconds / 10; // 秒の10の位
	digits.w = seconds % 10; // 秒の1の位

	m_transform->SetRect(digits);
}

void TimerUI::InitialMaterial(int width, int height)
{
	auto material = dynamic_cast<DefaultUi*>(m_material.get());

	material->SetPixelShader(CommonResources::GetInstance()->GetResources()->GetShaderResources()->GetNumberPS());
	material->SetWindowSize({ 1280.0f,720.0f });
	material->SetTextureSize({ (float)width, (float)height });
	material->SetUseTexture(1.0f);
	material->SetUseRuleTexture(0.0f);
	material->SetRuleProgress(0.0f);
	material->SetRuleInverse(0.0f);
}

void TimerUI::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	(void)messageID;
}

void TimerUI::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	(void)messageID;
	(void)sender;
}