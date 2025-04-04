#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"
#include "Framework/Resources/MaterialResources.h"
#include "Interface/IMaterial.h"
#include "Framework/Resources.h"

#include "Game/Material/PBRLit.h"
#include "Game/Material/DefaultUi.h"
#include "Game/Material/BalloonMaterial.h"


MaterialResources::MaterialResources()
{

}

void MaterialResources::Initialize(Resources* resources)
{
	// テクスチャのリソース
	auto textureResources = resources->GetTextureResources();
	auto shaderResources = resources->GetShaderResources();

	// デフォルトのマテリアルを作成
	m_defaultPBRLit = std::make_unique<PBRLit>();

	auto defaultPBRLit = dynamic_cast<PBRLit*>(m_defaultPBRLit.get());

	defaultPBRLit->Initialize(resources);
	defaultPBRLit->SetBaseColor(DirectX::SimpleMath::Vector4::One);
	defaultPBRLit->SetMatallic(0.3f);
	defaultPBRLit->SetSmoothness(0.7f);
	defaultPBRLit->SetUseBaseMap(1.0f);
	defaultPBRLit->SetUseNormalMap(0.0f);

	// テクスチャを設定
	defaultPBRLit->SetBaseMap(textureResources->GetPlayerTexture());
	defaultPBRLit->SetNormalMap(textureResources->GetWoodNormalMap());
	defaultPBRLit->SetSkyMap(textureResources->GetCubeMap());

	// 風船のマテリアルを作成
	m_balloon = std::make_unique<BalloonMaterial>();

	auto balloon = dynamic_cast<BalloonMaterial*>(m_balloon.get());

	balloon->Initialize(resources);
	balloon->SetBaseColor(DirectX::SimpleMath::Vector4::One);
	balloon->SetMatallic(0.0f);
	balloon->SetSmoothness(1.0f);
	balloon->SetUseBaseMap(5.0f);
	balloon->SetUseNormalMap(0.0f);

	// テクスチャを設定
	balloon->SetBaseMap(textureResources->GetBalloonTexture());
	balloon->SetNormalMap(textureResources->GetWoodNormalMap());
	balloon->SetSkyMap(textureResources->GetCubeMap());

	m_cloud = std::make_unique<PBRLit>();

	auto cloud = dynamic_cast<PBRLit*>(m_cloud.get());

	cloud->Initialize(resources);
	cloud->SetBaseColor({0.9f,0.9f,0.9f,0.7f});
	cloud->SetMatallic(0.0f);
	cloud->SetSmoothness(1.0f);
	cloud->SetUseBaseMap(0.0f);
	cloud->SetUseNormalMap(0.0f);

	// テクスチャを設定
	cloud->SetBaseMap(nullptr);
	cloud->SetNormalMap(nullptr);
	cloud->SetSkyMap(textureResources->GetCubeMap());

	// defaultPBRLit->UpdateConstantBuffer();
}