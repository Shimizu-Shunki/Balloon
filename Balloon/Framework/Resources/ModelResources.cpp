#include "Framework/pch.h"
#include "Framework/Resources/ModelResources.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources.h"
#include <Framework/Microsoft/ReadData.h>
#include <unordered_map>

ModelResources::ModelResources()
	:
	m_playerHeadModel{},
	m_playerBodyModel{},
	m_playerRightArmModel{},
	m_playerLeftArmModel{},
	m_playerRightFootModel{},
	m_playerLeftFootModel{},
	m_enemyHeadModel{},
	m_balloonModel{},
	m_cloudModel{}
{

}

void ModelResources::LoadResource(const nlohmann::json& data)
{
	// �f�o�C�X
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	// �G�t�F�N�g�t�@�N�g���𐶐�����
	std::unique_ptr<DirectX::EffectFactory> effectFactory = std::make_unique<DirectX::EffectFactory>(device);

	// PlayerModel�̃p�X���擾
	std::unordered_map<std::string, std::wstring> modelPaths;
	if (data.contains("PlayerModels")) {
		for (const auto& entry : data["PlayerModels"]) {
			for (const auto& [key, value] : entry.items()) {
				modelPaths[key] = Resources::ConvertToWString(value);
			}
		}
	}
	// ���\�[�X�f�B���N�g����ݒ肷��
	effectFactory->SetDirectory(modelPaths["Directory"].c_str());
	// �v���C���[�@�����f�������[�h����
	m_playerHeadModel = DirectX::Model::CreateFromCMO(device, modelPaths["Head"].c_str(), *effectFactory);
	// �v���C���[�@�̃��f�������[�h����
	m_playerBodyModel = DirectX::Model::CreateFromCMO(device, modelPaths["Body"].c_str(), *effectFactory);
	// �v���C���[�@�E�r���f�������[�h����
	m_playerRightArmModel = DirectX::Model::CreateFromCMO(device, modelPaths["RightArm"].c_str(), *effectFactory);
	// �v���C���[�@���r���f�������[�h����
	m_playerLeftArmModel = DirectX::Model::CreateFromCMO(device, modelPaths["LeftArm"].c_str(), *effectFactory);
	// �v���C���[�@�E�����f�������[�h����
	m_playerRightFootModel = DirectX::Model::CreateFromCMO(device, modelPaths["RightFoot"].c_str(), *effectFactory);
	// �v���C���[�@�������f�������[�h����
	m_playerLeftFootModel = DirectX::Model::CreateFromCMO(device, modelPaths["LeftFoot"].c_str(), *effectFactory);

	// EnemyModel�̃p�X���擾
	if (data.contains("EnemyModel")) {
		for (const auto& entry : data["EnemyModel"]) {
			for (const auto& [key, value] : entry.items()) {
				modelPaths[key] = Resources::ConvertToWString(value);
			}
		}
	}
	// ���\�[�X�f�B���N�g����ݒ�
	effectFactory->SetDirectory(modelPaths["Directory"].c_str());
	// �G�@�����f�������[�h����
	m_enemyHeadModel = DirectX::Model::CreateFromCMO(device, modelPaths["Head"].c_str(), *effectFactory);

	// Model�̃p�X���擾
	if (data.contains("Model")) {
		for (const auto& entry : data["Model"]) {
			for (const auto& [key, value] : entry.items()) {
				modelPaths[key] = Resources::ConvertToWString(value);
			}
		}
	}
	// ���\�[�X�f�B���N�g����ݒ肷��
	effectFactory->SetDirectory(modelPaths["Directory"].c_str());
	// �v���C���[�@���D���f�������[�h����
	m_balloonModel = DirectX::Model::CreateFromCMO(device, modelPaths["Balloon"].c_str(), *effectFactory);
	// �v���C���[�@�_���f�������[�h����
	m_cloudModel = DirectX::Model::CreateFromCMO(device, modelPaths["Cloud"].c_str(), *effectFactory);
}