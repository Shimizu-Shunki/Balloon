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
	// デバイス
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	// エフェクトファクトリを生成する
	std::unique_ptr<DirectX::EffectFactory> effectFactory = std::make_unique<DirectX::EffectFactory>(device);

	// PlayerModelのパスを取得
	std::unordered_map<std::string, std::wstring> modelPaths;
	if (data.contains("PlayerModels")) {
		for (const auto& entry : data["PlayerModels"]) {
			for (const auto& [key, value] : entry.items()) {
				modelPaths[key] = Resources::ConvertToWString(value);
			}
		}
	}
	// リソースディレクトリを設定する
	effectFactory->SetDirectory(modelPaths["Directory"].c_str());
	// プレイヤー　頭モデルをロードする
	m_playerHeadModel = DirectX::Model::CreateFromCMO(device, modelPaths["Head"].c_str(), *effectFactory);
	// プレイヤー　体モデルをロードする
	m_playerBodyModel = DirectX::Model::CreateFromCMO(device, modelPaths["Body"].c_str(), *effectFactory);
	// プレイヤー　右腕モデルをロードする
	m_playerRightArmModel = DirectX::Model::CreateFromCMO(device, modelPaths["RightArm"].c_str(), *effectFactory);
	// プレイヤー　左腕モデルをロードする
	m_playerLeftArmModel = DirectX::Model::CreateFromCMO(device, modelPaths["LeftArm"].c_str(), *effectFactory);
	// プレイヤー　右足モデルをロードする
	m_playerRightFootModel = DirectX::Model::CreateFromCMO(device, modelPaths["RightFoot"].c_str(), *effectFactory);
	// プレイヤー　左足モデルをロードする
	m_playerLeftFootModel = DirectX::Model::CreateFromCMO(device, modelPaths["LeftFoot"].c_str(), *effectFactory);

	// EnemyModelのパスを取得
	if (data.contains("EnemyModel")) {
		for (const auto& entry : data["EnemyModel"]) {
			for (const auto& [key, value] : entry.items()) {
				modelPaths[key] = Resources::ConvertToWString(value);
			}
		}
	}
	// リソースディレクトリを設定
	effectFactory->SetDirectory(modelPaths["Directory"].c_str());
	// 敵　頭モデルをロードする
	m_enemyHeadModel = DirectX::Model::CreateFromCMO(device, modelPaths["Head"].c_str(), *effectFactory);

	// Modelのパスを取得
	if (data.contains("Model")) {
		for (const auto& entry : data["Model"]) {
			for (const auto& [key, value] : entry.items()) {
				modelPaths[key] = Resources::ConvertToWString(value);
			}
		}
	}
	// リソースディレクトリを設定する
	effectFactory->SetDirectory(modelPaths["Directory"].c_str());
	// プレイヤー　風船モデルをロードする
	m_balloonModel = DirectX::Model::CreateFromCMO(device, modelPaths["Balloon"].c_str(), *effectFactory);
	// プレイヤー　雲モデルをロードする
	m_cloudModel = DirectX::Model::CreateFromCMO(device, modelPaths["Cloud"].c_str(), *effectFactory);
}