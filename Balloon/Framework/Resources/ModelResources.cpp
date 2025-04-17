// ============================================
// 
// ファイル名: ModelResources.cpp
// 概要: モデルのリソースを管理するクラス（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================

#include "pch.h"
#include "Framework/Resources/ModelResources.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include <Framework/Microsoft/ReadData.h>

/// <summary>
/// コンストラクタ
/// </summary>
ModelResources::ModelResources()
	:
	m_models{}
{

}

/// <summary>
/// モデルのリソースをロードする
/// </summary>
/// <param name="data">Jsonデータ</param>
void ModelResources::LoadResource(const nlohmann::json& data)
{
	// デバイス
	ID3D11Device1* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	// エフェクトファクトリを生成する
	std::unique_ptr<DirectX::EffectFactory> effectFactory = std::make_unique<DirectX::EffectFactory>(device);

	// モデルの各ディレクトリを取得する
	const std::wstring directory       = Resources::GetDirectoryFromJSON(data,"ModelDirectory");
	const std::wstring playerDirectory = Resources::GetDirectoryFromJSON(data,"PlayerModelDirectory");
	const std::wstring EnemyDirectory  = Resources::GetDirectoryFromJSON(data,"EnemyModelDirectory");
	// ディレクトリを設定する
	effectFactory->SetDirectory(directory.c_str());

	// モデルをロードする
	if (data.contains("Models") && data["Models"].is_object()) {
		const auto& models = data["Models"];

		for (const auto& [key, value] : models.items()) 
		{
			// パス構築
			std::wstring path = directory + L"/" + Resources::ConvertToWString(value);

			// モデルのロード
			m_models[key] = DirectX::Model::CreateFromCMO(device, path.c_str(), *effectFactory);
		}
	}

	// プレイヤーモデルのディレクトリを設定する
	effectFactory->SetDirectory(playerDirectory.c_str());

	// プレイヤーモデルをロードする
	if (data.contains("PlayerModels") && data["PlayerModels"].is_object()) {
		const auto& models = data["PlayerModels"];

		for (const auto& [key, value] : models.items())
		{
			// パス構築
			std::wstring path = playerDirectory + L"/" + Resources::ConvertToWString(value);

			// モデルのロード
			m_models[key] = DirectX::Model::CreateFromCMO(device, path.c_str(), *effectFactory);
		}
	}

	// 敵モデルのディレクトリを設定する
	effectFactory->SetDirectory(EnemyDirectory.c_str());

	// 敵モデルをロードする
	if (data.contains("EnemyModel") && data["EnemyModel"].is_object()) {
		const auto& models = data["EnemyModel"];

		for (const auto& [key, value] : models.items())
		{
			// パス構築
			std::wstring path = EnemyDirectory + L"/" + Resources::ConvertToWString(value);

			// モデルのロード
			m_models[key] = DirectX::Model::CreateFromCMO(device, path.c_str(), *effectFactory);
		}
	}
}