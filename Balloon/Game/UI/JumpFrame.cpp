#include "Framework/pch.h"
#include "Game/UI/JumpFrame.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"

JumpFrame::JumpFrame()
{
	

}


void JumpFrame::Initialize()
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

	// シェーダーをロードする
	m_spriteMaterial->LoadVertexShader(L"Resources/Shaders/cso/UI_VS.cso");
	m_spriteMaterial->LoadGeometryShader(L"Resources/Shaders/cso/UI_GS.cso");
	m_spriteMaterial->LoadPixelShader(L"Resources/Shaders/cso/UI_PS.cso");

	int width, height;

	// 画像をロード
	m_spriteMaterial->LoadTexture(commonResources->GetResources()->GetJampFrame(), width, height);

	m_constBuffer.windowSize = { 1280.0f,720.0f };
	m_constBuffer.textureSize = { (float)width,(float)height };
	m_constBuffer.useTexture = 1;
	m_constBuffer.useRuleTexture = 0;
	m_constBuffer.ruleProgress = 0.0f;
	m_constBuffer.ruleInverse = 0;

	m_transform->SetLocalPosition({ 1280.0f / 4.0f, 720.0f / 3.0f,0.0f });

	m_vertexBuffer.position = DirectX::SimpleMath::Vector4(
		m_transform->GetLocalPosition().x,
		m_transform->GetLocalPosition().y,
		m_transform->GetLocalPosition().z,
		1.0f
	);
	m_vertexBuffer.scale = DirectX::SimpleMath::Vector3::Zero;

	m_vertexBuffer.color = DirectX::SimpleMath::Vector4::One;

	m_vertexBuffer.rect = { 0.0f , 0.0f , (float)width,(float)height };

	m_vertexBuffer.rotate = DirectX::SimpleMath::Vector3::Zero;


	m_spriteMaterial->SetVertexBuffer(m_vertexBuffer);

	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::Zero);
}


void JumpFrame::Update()
{
	m_vertexBuffer.scale = m_transform->GetLocalScale();

	m_spriteMaterial->SetVertexBuffer(m_vertexBuffer);
}