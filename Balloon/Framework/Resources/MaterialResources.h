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
	// �f�t�H���gPBRLit
	std::unique_ptr<IMaterial> m_defaultPBRLit;
	// UI
	std::unique_ptr<IMaterial> m_defaultUi;

};