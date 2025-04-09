// ============================================
// 
// �t�@�C����: MaterialResources.h
// �T�v: MaterialResources.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================

#pragma once
#include "Interface/IMaterial.h"

class PBRLit;
class IMaterial;
class Resources;

class MaterialResources
{
public:
	// �f�t�H���g��PBRLit�}�e���A�����擾����
	IMaterial* GetDefaultPBRLit() const { return m_defaultPBRLit.get(); }
	// ���D�̃}�e���A�����擾����
	IMaterial* GetBalloon() const { return m_balloon.get(); }
	// �_�̃}�e���A�����擾����
	IMaterial* GetCloud() const { return m_cloud.get(); }

public:
	MaterialResources(const MaterialResources&) = delete;             // �R�s�[�֎~
	MaterialResources& operator=(const MaterialResources&) = delete;  // �R�s�[����֎~
	MaterialResources(const MaterialResources&&) = delete;            // ���[�u�֎~
	MaterialResources& operator=(const MaterialResources&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static MaterialResources* GetInstance()
	{
		static MaterialResources instance;
		return &instance;
	}
private:
	// �R���X�g���N�^
	MaterialResources();

public:
	// ����������
	void Initialize(Resources* resources);

private:
	// �v���C���[
	std::unique_ptr<IMaterial> m_defaultPBRLit;
	// ���D
	std::unique_ptr<IMaterial> m_balloon;
	// ���D
	std::unique_ptr<IMaterial> m_cloud;
	// UI
	std::unique_ptr<IMaterial> m_defaultUi;

};