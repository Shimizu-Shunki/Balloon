#include "Framework/pch.h"
#include "Framework/Resources/TextureResources.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources.h"
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
	m_cubeMap{},
	m_eveningCubeMap{}
{

}



void TextureResources::LoadResource(const nlohmann::json& data)
{
    // デバイス
    ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

    // Textures のパスを取得
    std::unordered_map<std::string, std::wstring> texturePaths;
    if (data.contains("Textures")) {
        for (const auto& entry : data["Textures"]) {
            for (const auto& [key, value] : entry.items()) {
                texturePaths[key] = Resources::ConvertToWString(value);
            }
        }
    }

    // タイトルロゴ
    DirectX::CreateWICTextureFromFile(
        device, texturePaths["Logo"].c_str(), nullptr, m_titleLogo.ReleaseAndGetAddressOf());

	// スタートテキスト
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["StartText"].c_str(), nullptr, m_startText.ReleaseAndGetAddressOf());
	// スペースキー
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["SpaceKey"].c_str(), nullptr, m_spaceKey.ReleaseAndGetAddressOf());

	// ジャンプフレーム
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["JumpFrameUI"].c_str(), nullptr, m_jampFrame.ReleaseAndGetAddressOf());
	// ジャンプメモリ
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["JumpBar"].c_str(), nullptr, m_jampMemori.ReleaseAndGetAddressOf());
	// タイムフレーム
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["TimeFrame"].c_str(), nullptr, m_timeFrame.ReleaseAndGetAddressOf());
	// タイムゲージ
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["TimerBar"].c_str(), nullptr, m_timeGage.ReleaseAndGetAddressOf());
	// ルール画像
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Fade"].c_str(), nullptr, m_ruleTexture.ReleaseAndGetAddressOf());
	// ゲームクリアテキスト画像
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["ClearText"].c_str(), nullptr, m_clearText.ReleaseAndGetAddressOf());
	// ゲームオーバーテキスト画像
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["FailedText"].c_str(), nullptr, m_failedText.ReleaseAndGetAddressOf());
	// 海画像
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Sea"].c_str(), nullptr, m_SeaTexture.ReleaseAndGetAddressOf());

	// レディゴー
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["ReadyGo"].c_str(), nullptr, m_readyGo.ReleaseAndGetAddressOf());
	// ナンバーズ
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Numbers"].c_str(), nullptr, m_numbers.ReleaseAndGetAddressOf());
	// メニューボタンテキスト
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["MenuButton"].c_str(), nullptr, m_menuButtonText.ReleaseAndGetAddressOf());
	// キー操作説明
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["KeyGuide"].c_str(), nullptr, m_keyGuide.ReleaseAndGetAddressOf());
	// キー操作説明
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["MenuButtonFrame"].c_str(), nullptr, m_menuButtonFrame.ReleaseAndGetAddressOf());
	// キー操作説明
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["MenuButtonFrame2"].c_str(), nullptr, m_menuButtonFrame2.ReleaseAndGetAddressOf());





	// プレイヤー画像
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Player"].c_str(), nullptr, m_playerTexture.ReleaseAndGetAddressOf());
	// 敵画像
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Enemy"].c_str(), nullptr, m_enemyTexture.ReleaseAndGetAddressOf());

	if (data.contains("Textures_NormalMaps")) {
		for (const auto& entry : data["Textures_NormalMaps"]) {
			for (const auto& [key, value] : entry.items()) {
				texturePaths[key] = Resources::ConvertToWString(value);
			}
		}
	}

	// 肉 ノーマルマップ
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Meat"].c_str(), nullptr, m_meatNormalMap.ReleaseAndGetAddressOf());
	// 木　ノーマルマップ
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Wood"].c_str(), nullptr, m_woodNormalMap.ReleaseAndGetAddressOf());
	// 岩　ノーマルマップ
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Rock"].c_str(), nullptr, m_rockNormalMap.ReleaseAndGetAddressOf());
	// 海　ノーマルマップ
	DirectX::CreateWICTextureFromFile(
		device, texturePaths["Sea"].c_str(), nullptr, m_seaNormalMap.ReleaseAndGetAddressOf());

	if (data.contains("Textures_DDS")) {
		for (const auto& entry : data["Textures_DDS"]) {
			for (const auto& [key, value] : entry.items()) {
				texturePaths[key] = Resources::ConvertToWString(value);
			}
		}
	}

	// スカイマップ
	DirectX::CreateDDSTextureFromFile(
		device, texturePaths["CubeMap"].c_str(), nullptr, m_cubeMap.ReleaseAndGetAddressOf());

	// スカイマップ
	DirectX::CreateDDSTextureFromFile(
		device, texturePaths["EveningCubeMap"].c_str(), nullptr, m_eveningCubeMap.ReleaseAndGetAddressOf());

	texturePaths.clear();
}