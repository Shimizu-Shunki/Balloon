#include "Framework/pch.h"
#include "Game/UI/ClearText.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"

ClearText::ClearText()
{
	

}


void ClearText::Initialize()
{
	auto commonResources = CommonResources::GetInstance();

	
	// Transform�̍쐬
	m_transform = std::make_unique<Transform>();

	// �}�e���A���̍쐬
	m_spriteMaterial = std::make_unique<SpriteMaterial>(
		commonResources->GetDeviceResources()->GetD3DDevice(), commonResources->GetDeviceResources()->GetD3DDeviceContext());

	// �萔�o�b�t�@��ݒ�
	m_spriteMaterial->SetConstBuffer<ConstBuffer>();

	// �V�F�[�_�[��ݒ�
	m_spriteMaterial->SetVertexShader  (commonResources->GetResources()->GetUI_VS());
	m_spriteMaterial->SetGeometryShader(commonResources->GetResources()->GetUI_GS());
	m_spriteMaterial->SetPixelShader   (commonResources->GetResources()->GetUI_PS());

	int width, height;

	// �摜�����[�h
	m_spriteMaterial->SetTexture(commonResources->GetResources()->GetClearTextTexture(), width, height);

	m_constBuffer.windowSize = { 1280.0f,720.0f };
	m_constBuffer.textureSize = { (float)width,(float)height };
	m_constBuffer.useTexture = 1;
	m_constBuffer.useRuleTexture = 0;
	m_constBuffer.ruleProgress = 0.0f;
	m_constBuffer.ruleInverse = 0;

	m_transform->SetLocalPosition({ 1280.0f / 2.0f , -50.0f , 0.0f });
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);

	m_vertexBuffer.position = DirectX::SimpleMath::Vector4(
		m_transform->GetLocalPosition().x,
		m_transform->GetLocalPosition().y,
		m_transform->GetLocalPosition().z,
		1.0f
	);

	m_vertexBuffer.scale = m_transform->GetLocalScale();
	m_vertexBuffer.color = DirectX::SimpleMath::Vector4::One;
	m_vertexBuffer.rect = { 0.0f , 0.0f , (float)width , (float)height };
	m_vertexBuffer.rotate = DirectX::SimpleMath::Vector3::Zero;

	m_spriteMaterial->SetVertexBuffer(m_vertexBuffer);

	// Tween�N��
	m_transform->GetTween()->DOMoveY(720.0f * 0.25f, 1.0f)
		.SetDelay(2.0f).SetEase(Tween::EasingType::EaseOutBounce);

	commonResources->GetRenderManager()->AddSprite(this);

}


void ClearText::Update()
{
	m_spriteMaterial->UpdateConstBuffer<ConstBuffer>(m_constBuffer, 0);

	m_vertexBuffer.position = DirectX::SimpleMath::Vector4(
		m_transform->GetLocalPosition().x,
		m_transform->GetLocalPosition().y,
		m_transform->GetLocalPosition().z,
		1.0f
	);
	m_vertexBuffer.scale = m_transform->GetLocalScale();

	m_spriteMaterial->SetVertexBuffer(m_vertexBuffer);
	
}