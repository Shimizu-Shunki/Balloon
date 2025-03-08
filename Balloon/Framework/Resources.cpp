#include "Framework/pch.h"
#include "Framework/Resources.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"
#include "Framework/Resources/MaterialResources.h"

Resources::Resources()
	
{
	// �C���X�^���X���擾����
	m_modelResources    = ModelResources::GetInstance();
	m_shaderResources   = ShaderResources::GetInstance();
	m_textureResources  = TextureResources::GetInstance();
	m_materialResources = MaterialResources::GetInstance();
}


// ���\�[�X�����[�h����
void Resources::LoadResource()
{
	// JSON�t�@�C�����J��
	std::ifstream file("Resources/Json/GameResourceData.json");
	assert(file);
	// JSON �����[�h
	nlohmann::json data;
	file >> data; 

	// ���f�������[�h����
	m_modelResources->LoadResource(data);
	// �V�F�[�_�[�����[�h����
	m_shaderResources->LoadResource(data);
	// �e�N�X�`�������[�h����
	m_textureResources->LoadResource(data);

	m_materialResources->Initialize(this);
}
