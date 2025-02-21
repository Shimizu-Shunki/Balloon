#include "Framework/pch.h"
#include "Game/UI/JumpFrame.h"
#include "Framework/CommonResources.h"
#include "Framework/Tween/Tween.h"

JumpFrame::JumpFrame()
{
	

}


void JumpFrame::Initialize()
{
	// 共有リソース
	auto commonResources = CommonResources::GetInstance();

	// Transformの作成
	m_transform = std::make_unique<Transform>();

	// マテリアルの作成
	m_spriteMaterial = std::make_unique<SpriteMaterial>(
		commonResources->GetDeviceResources()->GetD3DDevice(), commonResources->GetDeviceResources()->GetD3DDeviceContext());

	// 定数バッファを設定
	m_spriteMaterial->SetConstBuffer<ConstBuffer>();

	// シェーダーを設定
	m_spriteMaterial->SetVertexShader  (commonResources->GetResources()->GetUI_VS());
	m_spriteMaterial->SetGeometryShader(commonResources->GetResources()->GetUI_GS());
	m_spriteMaterial->SetPixelShader   (commonResources->GetResources()->GetUI_PS());

	// 画像を設定
	int width, height;
	m_spriteMaterial->SetTexture(commonResources->GetResources()->GetJampFrame(), width, height);

	// 定数バッファ数値設定
	m_constBuffer.windowSize     = { 1280.0f , 720.0f };
	m_constBuffer.textureSize    = { (float)width , (float)height };
	m_constBuffer.useTexture     = 1;
	m_constBuffer.useRuleTexture = 0;
	m_constBuffer.ruleProgress   = 0.0f;
	m_constBuffer.ruleInverse    = 0;


	// 座標設定
	m_transform->SetLocalPosition({ 300, 100 , 0.0f });
	// 回転設定
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	// スケール設定
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One * 0.5f);

	// 頂点バッファを設定
	m_vertexBuffer.position = DirectX::SimpleMath::Vector4(
		m_transform->GetLocalPosition().x,
		m_transform->GetLocalPosition().y,
		m_transform->GetLocalPosition().z,
		1.0f
	);
	m_vertexBuffer.scale = m_transform->GetLocalScale();

	m_vertexBuffer.color = DirectX::SimpleMath::Vector4::One;

	m_vertexBuffer.rect = { 0.0f , 0.0f , (float)width , (float)height };

	m_vertexBuffer.rotate = m_transform->GetLocalRotation().ToEuler();

	// 頂点バッファをマテリアルに渡す
	m_spriteMaterial->SetVertexBuffer(m_vertexBuffer);

	// スプライトを描画マネージャーに追加する
	commonResources->GetRenderManager()->AddSprite(this);
}


void JumpFrame::Update()
{
	m_spriteMaterial->UpdateConstBuffer<ConstBuffer>(m_constBuffer, 0);

	m_spriteMaterial->SetVertexBuffer(m_vertexBuffer);
}