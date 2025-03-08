#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/TextureResources.h"
#include "Framework/Resources/MaterialResources.h"
#include "Interface/IMaterial.h"
#include "Framework/Resources.h"

#include "Game/Material/PBRLit.h"


MaterialResources::MaterialResources()
{

}

void MaterialResources::Initialize(Resources* resources)
{
	// �e�N�X�`���̃��\�[�X
	auto textureResources = resources->GetTextureResources();

	// �f�t�H���g�̃}�e���A�����쐬
	m_defaultPBRLit = std::make_unique<PBRLit>();

	auto defaultPBRLit = dynamic_cast<PBRLit*>(m_defaultPBRLit.get());

	defaultPBRLit->Initialize(resources);
	defaultPBRLit->SetBaseColor(DirectX::SimpleMath::Vector4::One);
	defaultPBRLit->SetMatallic(0.3f);
	defaultPBRLit->SetSmoothness(0.7f);
	defaultPBRLit->SetUseBaseMap(1.0f);
	defaultPBRLit->SetUseNormalMap(0.0f);

	// �e�N�X�`����ݒ�
	defaultPBRLit->SetBaseMap(textureResources->GetPlayerTexture());
	defaultPBRLit->SetNormalMap(textureResources->GetWoodNormalMap());
	defaultPBRLit->SetSkyMap(textureResources->GetCubeMap());

	defaultPBRLit->UpdateConstantBuffer();
}