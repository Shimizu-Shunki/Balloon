#include "Framework/pch.h"
#include "Game/UI/JumpMemory.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"

JumpMemory::JumpMemory()
	:
	m_transform{},
	m_spriteMaterial{},
	m_vertexBuffer{},
	m_constBuffer{}
{
}


void JumpMemory::Initialize()
{
	auto commonResources = CommonResources::GetInstance();

	commonResources->GetRenderManager()->AddSprite(this);

	// Transformの作成
	m_transform = std::make_unique<Transform>();

	// マテリアルの作成
	m_spriteMaterial = std::make_unique<SpriteMaterial>(
		commonResources->GetDeviceResources()->GetD3DDevice(), commonResources->GetDeviceResources()->GetD3DDeviceContext());

	// 定数バッファを設定
	m_spriteMaterial->SetConstBuffer<ConstBuffer>();

	// シェーダーを設定
	m_spriteMaterial->SetVertexShader(commonResources->GetResources()->GetShaderResources()->GetUI_VS());
	m_spriteMaterial->SetGeometryShader(commonResources->GetResources()->GetShaderResources()->GetUI_GS());
	m_spriteMaterial->SetPixelShader(commonResources->GetResources()->GetShaderResources()->GetUI_PS());

	int width, height;

	// 画像をロード
	m_spriteMaterial->SetTexture(commonResources->GetResources()->GetTextureResources()->GetJampMemori(), width, height);

	m_constBuffer.windowSize = { 1280.0f,720.0f };
	m_constBuffer.textureSize = { (float)width ,(float)height };
	m_constBuffer.useTexture = 1;
	m_constBuffer.useRuleTexture = 0;
	m_constBuffer.ruleProgress = 0.0f;
	m_constBuffer.ruleInverse = 0;

	m_texSizeW = (float)width;
	m_texSizeH = (float)height;

	m_transform->SetLocalPosition({ 1280.0f / 4.0f, 200.0f,0.0f });

	m_vertexBuffer.position = DirectX::SimpleMath::Vector4(
		m_transform->GetLocalPosition().x,
		m_transform->GetLocalPosition().y,
		m_transform->GetLocalPosition().z,
		1.0f
	);
	m_vertexBuffer.scale = DirectX::SimpleMath::Vector3::One;

	m_vertexBuffer.color = DirectX::SimpleMath::Vector4::One;

	m_vertexBuffer.rect = { 0.0f , 0.0f , (float)width,(float)height };

	m_vertexBuffer.rotate = DirectX::SimpleMath::Vector3::Zero;


	m_spriteMaterial->SetVertexBuffer(m_vertexBuffer);

	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One * 0.4f);
}


void JumpMemory::Update()
{
	m_spriteMaterial->UpdateConstBuffer<ConstBuffer>(m_constBuffer, 0);

	m_vertexBuffer.scale = m_transform->GetLocalScale();

	m_vertexBuffer.position = DirectX::SimpleMath::Vector4(
		m_transform->GetLocalPosition().x,
		m_transform->GetLocalPosition().y,
		m_transform->GetLocalPosition().z,
		1.0f
	);

	m_spriteMaterial->SetVertexBuffer(m_vertexBuffer);
}