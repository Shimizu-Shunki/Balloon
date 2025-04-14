// ============================================
// 
// �t�@�C����: Resources.h
// �T�v: Resources.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================

#pragma once
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

class CommonResources;

class ModelResources;
class ShaderResources;
class TextureResources;
class MaterialResources;
class StageResources;

// Resources�N���X���`����
class Resources
{
public:
	// �ȈՓI�� UTF-8 �� UTF-16 �ϊ�
	static std::wstring ConvertToWString(const std::string& str) {
		return std::wstring(str.begin(), str.end()); 
	};

public:
	// ���f�����\�[�X���擾����
	ModelResources* GetModelResources() { return m_modelResources; }
	// �V�F�[�_�[���\�[�X���擾����
	ShaderResources* GetShaderResources() { return m_shaderResources; }
	// �e�N�X�`�����\�[�X���擾����
	TextureResources* GetTextureResources() { return m_textureResources; }
	// �}�e���A�����\�[�X���擾����
	MaterialResources* GetMaterialResources() { return m_materialResources; }
	// �X�e�[�W�f�[�^���擾����
	StageResources* GetStageResources() { return m_stageResources; }

public:
	Resources(const Resources&) = delete;             // �R�s�[�֎~
	Resources& operator=(const Resources&) = delete;  // �R�s�[����֎~
	Resources(const Resources&&) = delete;            // ���[�u�֎~
	Resources& operator=(const Resources&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static Resources* GetInstance()
	{
		static Resources instance;
		return &instance;
	}
	// ���\�[�X�����[�h����
	void LoadResource();

private:
	// �R���X�g���N�^
	Resources();
	
private:
	// ���f�����\�[�X
	ModelResources* m_modelResources;
	// �V�F�[�_�[���\�[�X
	ShaderResources* m_shaderResources;
	// �e�N�X�`�����\�[�X
	TextureResources* m_textureResources;
	// �}�e���A�����\�[�X
	MaterialResources* m_materialResources;
	// �X�e�[�W���\�[�X
	StageResources* m_stageResources;
};