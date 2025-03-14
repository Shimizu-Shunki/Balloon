#pragma once
#include <Model.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

class ModelResources
{
public:
	// ���f�����擾����
// �v���C���[�@�����f�����擾����
	DirectX::Model* GetPlayerHeadModel() { return m_playerHeadModel.get(); }
	// �v���C���[�@�̃��f�����擾����
	DirectX::Model* GetPlayerBodyModel() { return m_playerBodyModel.get(); }
	// �v���C���[�@�E�r���f�����擾����
	DirectX::Model* GetPlayerRightArmModel() { return m_playerRightArmModel.get(); }
	// �v���C���[�@���r���f�����擾����
	DirectX::Model* GetPlayerLeftArmModel() { return m_playerLeftArmModel.get(); }
	// �v���C���[�@�E�����f�����擾����
	DirectX::Model* GetPlayerRightFootModel() { return m_playerRightFootModel.get(); }
	// �v���C���[�@�������f�����擾����
	DirectX::Model* GetPlayerLeftFootModel() { return m_playerLeftFootModel.get(); }

	// �G�@�����f�����擾����
	DirectX::Model* GetEnemyHeadModel() { return m_enemyHeadModel.get(); }

	// ���D�̃��f�����擾����
	DirectX::Model* GetBalloonModel() { return m_balloonModel.get(); }
	// �_�̃��f�����擾����
	DirectX::Model* GetCloudModel() { return m_cloudModel.get(); }

public:
	ModelResources(const ModelResources&) = delete;             // �R�s�[�֎~
	ModelResources& operator=(const ModelResources&) = delete;  // �R�s�[����֎~
	ModelResources(const ModelResources&&) = delete;            // ���[�u�֎~
	ModelResources& operator=(const ModelResources&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static ModelResources* GetInstance()
	{
		static ModelResources instance;
		return &instance;
	}
	// ���\�[�X�����[�h����
	void LoadResource(const nlohmann::json& data);

private:
	// �R���X�g���N�^
	ModelResources();

private:
	// �v���C���[�@�����f��
	std::unique_ptr<DirectX::Model> m_playerHeadModel;
	// �v���C���[�@�̃��f��
	std::unique_ptr<DirectX::Model> m_playerBodyModel;
	// �v���C���[�@�E�r���f��
	std::unique_ptr<DirectX::Model> m_playerRightArmModel;
	// �v���C���[�@���r���f��
	std::unique_ptr<DirectX::Model> m_playerLeftArmModel;
	// �v���C���[�@�E�����f��
	std::unique_ptr<DirectX::Model> m_playerRightFootModel;
	// �v���C���[�@�������f��
	std::unique_ptr<DirectX::Model> m_playerLeftFootModel;

	// �G�@�����f��
	std::unique_ptr<DirectX::Model> m_enemyHeadModel;


	// ���D���f��
	std::unique_ptr<DirectX::Model> m_balloonModel;
	// �_�̃��f��
	std::unique_ptr<DirectX::Model> m_cloudModel;
};