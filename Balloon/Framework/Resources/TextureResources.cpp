#include "Framework/pch.h"
#include "Framework/Resources/TextureResources.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources.h"
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <unordered_map>


TextureResources::TextureResources()
	:
	m_titleLogo{},
	m_startText{},
	m_spaceKey{},
	m_jampFrame{},
	m_jampMemori{},
	m_timeFrame{},
	m_timeGage{},
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
	m_cubeMap{}
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

	// �X�^�[�g�e�L�X�g
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["StartText"].c_str(), nullptr, m_startText.ReleaseAndGetAddressOf());
	// �X�y�[�X�L�[
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["SpaceKey"].c_str(), nullptr, m_spaceKey.ReleaseAndGetAddressOf());

	// �W�����v�t���[��
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["JumpFrameUI"].c_str(), nullptr, m_jampFrame.ReleaseAndGetAddressOf());
	// �W�����v������
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["JumpBar"].c_str(), nullptr, m_jampMemori.ReleaseAndGetAddressOf());
	// �^�C���t���[��
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["TimeFrame"].c_str(), nullptr, m_timeFrame.ReleaseAndGetAddressOf());
	// �^�C���Q�[�W
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["TimerBar"].c_str(), nullptr, m_timeGage.ReleaseAndGetAddressOf());
	// �i���o�[�Y
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["numberx128"].c_str(), nullptr, m_numbers.ReleaseAndGetAddressOf());
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

	// �v���C���[�摜
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Player"].c_str(), nullptr, m_playerTexture.ReleaseAndGetAddressOf());
	// �G�摜
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Enemy"].c_str(), nullptr, m_enemyTexture.ReleaseAndGetAddressOf());

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
}