#include "Framework/pch.h"
#include "Framework/Resources/TextureResources.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources.h"
#include <unordered_map>



TextureResources::TextureResources()
	:
	m_titleLogo{},
	m_playerIcon{},
	m_playSceneKeysGuide{},
	m_timeFrame{},
	m_scoreFrame{},
	m_balloonGageFrame{},
	m_balloonGage{},
	m_heightMeter{},
	m_hpGage{},
	m_hpGageFrame{},
	m_numbers{},
	m_ruleTexture{},
	m_clearText{},
	m_failedText{},
	m_SeaTexture{},
	m_playerTexture{},
	m_enemyTexture{},
	m_meatNormalMap{},
	m_woodNormalMap{},
	m_rockNormalMap{},
	m_seaNormalMap{},
	m_cloudNormalMap{},
	m_cubeMap{},
	m_eveningCubeMap{},
	m_startText{}
{

}



void TextureResources::LoadResource(const nlohmann::json& data)
{
    // �f�o�C�X
    ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

    // Textures �̃p�X���擾
    std::unordered_map<std::string, std::wstring> texturePaths;
    if (data.contains("Textures")) {
        for (const auto& entry : data["Textures"]) {
            for (const auto& [key, value] : entry.items()) {
                texturePaths[key] = Resources::ConvertToWString(value);
            }
        }
    }

    // �^�C�g�����S
    DirectX::CreateWICTextureFromFile(
        device, texturePaths["Logo"].c_str(), nullptr, m_titleLogo.ReleaseAndGetAddressOf());


	// ���[���摜
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Fade"].c_str(), nullptr, m_ruleTexture.ReleaseAndGetAddressOf());
	// �Q�[���N���A�e�L�X�g�摜
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["ClearText"].c_str(), nullptr, m_clearText.ReleaseAndGetAddressOf());
	// �Q�[���I�[�o�[�e�L�X�g�摜
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["FailedText"].c_str(), nullptr, m_failedText.ReleaseAndGetAddressOf());
	// �C�摜
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Sea"].c_str(), nullptr, m_SeaTexture.ReleaseAndGetAddressOf());

	// ���f�B�S�[
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["ReadyGo"].c_str(), nullptr, m_readyGo.ReleaseAndGetAddressOf());
	// �i���o�[�Y
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Numbers"].c_str(), nullptr, m_numbers.ReleaseAndGetAddressOf());
	// �i���o�[�Y1
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Numbers1"].c_str(), nullptr, m_numbers1.ReleaseAndGetAddressOf());
	// ���j���[�{�^���e�L�X�g
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["MenuButton"].c_str(), nullptr, m_menuButtonText.ReleaseAndGetAddressOf());
	// �L�[�������
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["KeyGuide"].c_str(), nullptr, m_keyGuide.ReleaseAndGetAddressOf());
	// �L�[�������
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["MenuButtonFrame"].c_str(), nullptr, m_menuButtonFrame.ReleaseAndGetAddressOf());
	// �L�[�������
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["MenuButtonFrame2"].c_str(), nullptr, m_menuButtonFrame2.ReleaseAndGetAddressOf());
	// �X�^�[�g�e�L�X�g
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["StartText"].c_str(), nullptr, m_startText.ReleaseAndGetAddressOf());


	// �v���C���[�A�C�R��
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["PlayerIcon"].c_str(), nullptr, m_playerIcon.ReleaseAndGetAddressOf());
	// �v���C�V�[���L�[�K�C�h
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["PlaySceneKeysGuide"].c_str(), nullptr, m_playSceneKeysGuide.ReleaseAndGetAddressOf());
	// �^�C���t���[��
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["TimeFrame"].c_str(), nullptr, m_timeFrame.ReleaseAndGetAddressOf());
	// �X�R�A�t���[��
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["ScoreFrame"].c_str(), nullptr, m_scoreFrame.ReleaseAndGetAddressOf());
	// �o���[���Q�[�W�t���[��
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["BalloonGageFrame"].c_str(), nullptr, m_balloonGageFrame.ReleaseAndGetAddressOf());
	// �o���[���Q�[�W
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["BalloonGage"].c_str(), nullptr, m_balloonGage.ReleaseAndGetAddressOf());
	// �������[�^�[
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["HeightMeter"].c_str(), nullptr, m_heightMeter.ReleaseAndGetAddressOf());
	// HP�Q�[�W
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["HPGage"].c_str(), nullptr, m_hpGage.ReleaseAndGetAddressOf());
	// HP�Q�[�W�t���[��
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["HPGageFrame"].c_str(), nullptr, m_hpGageFrame.ReleaseAndGetAddressOf());


	// �v���C���[�摜
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Player"].c_str(), nullptr, m_playerTexture.ReleaseAndGetAddressOf());
	// �G�摜
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Enemy"].c_str(), nullptr, m_enemyTexture.ReleaseAndGetAddressOf());
	
	if (data.contains("Textures_NormalMaps")) {
		for (const auto& entry : data["Textures_NormalMaps"]) {
			for (const auto& [key, value] : entry.items()) {
				texturePaths[key] = Resources::ConvertToWString(value);
			}
		}
	}

	// �� �m�[�}���}�b�v
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Meat"].c_str(), nullptr, m_meatNormalMap.ReleaseAndGetAddressOf());
	// �؁@�m�[�}���}�b�v
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Wood"].c_str(), nullptr, m_woodNormalMap.ReleaseAndGetAddressOf());
	// ��@�m�[�}���}�b�v
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Rock"].c_str(), nullptr, m_rockNormalMap.ReleaseAndGetAddressOf());
	// �C�@�m�[�}���}�b�v
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Sea"].c_str(), nullptr, m_seaNormalMap.ReleaseAndGetAddressOf());
	// �_�@�m�[�}���}�b�v
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Cloud"].c_str(), nullptr, m_cloudNormalMap.ReleaseAndGetAddressOf());

	


	if (data.contains("Textures_DDS")) {
		for (const auto& entry : data["Textures_DDS"]) {
			for (const auto& [key, value] : entry.items()) {
				texturePaths[key] = Resources::ConvertToWString(value);
			}
		}
	}

	// �X�J�C�}�b�v
	DirectX::CreateDDSTextureFromFile(
		device, texturePaths["CubeMap"].c_str(), nullptr, m_cubeMap.ReleaseAndGetAddressOf());

	// �X�J�C�}�b�v
	DirectX::CreateDDSTextureFromFile(
		device, texturePaths["EveningCubeMap"].c_str(), nullptr, m_eveningCubeMap.ReleaseAndGetAddressOf());

	// ���D�摜
	DirectX::CreateDDSTextureFromFile(
		device, texturePaths["Balloon"].c_str(), nullptr, m_balloonTexture.ReleaseAndGetAddressOf());

	texturePaths.clear();
}