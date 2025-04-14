// ============================================
// 
// �t�@�C����: Resources.cpp
// �T�v: �e�탊�\�[�X�̊Ǘ��Ɠǂݍ��݂��s���N���X�i�V���O���g���j
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Framework/Resources.h"
#include <iostream>
#include <fstream>

#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"
#include "Framework/Resources/MaterialResources.h"
#include "Framework/Resources/StageResources.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Resources::Resources()
	
{
	// �C���X�^���X���擾����
	m_modelResources    = ModelResources::GetInstance();
	m_shaderResources   = ShaderResources::GetInstance();
	m_textureResources  = TextureResources::GetInstance();
	m_materialResources = MaterialResources::GetInstance();
	m_stageResources    = StageResources::GetInstance();
}


/// <summary>
/// �e���\�[�X�̃��[�h
/// </summary>
void Resources::LoadResource()
{
	// JSON�t�@�C�����J��
	std::ifstream file("Resources/Json/GameResourceData.json");
	assert(file);
	// JSON �����[�h
	nlohmann::json data;
	file >> data; 

	// JSON�t�@�C�����J��
	std::ifstream StageDatafile("Resources/Json/StageData.json");
	assert(StageDatafile);
	// JSON �����[�h
	nlohmann::json StageData;
	StageDatafile >> StageData;

	// ���f�������[�h����
	m_modelResources->LoadResource(data);
	// �V�F�[�_�[�����[�h����
	m_shaderResources->LoadResource(data);
	// �e�N�X�`�������[�h����
	m_textureResources->LoadResource(data);
	// �}�e���A���̏���������
	m_materialResources->Initialize(this);

	m_stageResources->LoadResource(StageData);
}
