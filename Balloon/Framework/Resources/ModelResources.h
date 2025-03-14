#pragma once
#include <Model.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

class ModelResources
{
public:
	// モデルを取得する
// プレイヤー　頭モデルを取得する
	DirectX::Model* GetPlayerHeadModel() { return m_playerHeadModel.get(); }
	// プレイヤー　体モデルを取得する
	DirectX::Model* GetPlayerBodyModel() { return m_playerBodyModel.get(); }
	// プレイヤー　右腕モデルを取得する
	DirectX::Model* GetPlayerRightArmModel() { return m_playerRightArmModel.get(); }
	// プレイヤー　左腕モデルを取得する
	DirectX::Model* GetPlayerLeftArmModel() { return m_playerLeftArmModel.get(); }
	// プレイヤー　右足モデルを取得する
	DirectX::Model* GetPlayerRightFootModel() { return m_playerRightFootModel.get(); }
	// プレイヤー　左足モデルを取得する
	DirectX::Model* GetPlayerLeftFootModel() { return m_playerLeftFootModel.get(); }

	// 敵　頭モデルを取得する
	DirectX::Model* GetEnemyHeadModel() { return m_enemyHeadModel.get(); }

	// 風船のモデルを取得する
	DirectX::Model* GetBalloonModel() { return m_balloonModel.get(); }
	// 雲のモデルを取得する
	DirectX::Model* GetCloudModel() { return m_cloudModel.get(); }

public:
	ModelResources(const ModelResources&) = delete;             // コピー禁止
	ModelResources& operator=(const ModelResources&) = delete;  // コピー代入禁止
	ModelResources(const ModelResources&&) = delete;            // ムーブ禁止
	ModelResources& operator=(const ModelResources&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static ModelResources* GetInstance()
	{
		static ModelResources instance;
		return &instance;
	}
	// リソースをロードする
	void LoadResource(const nlohmann::json& data);

private:
	// コンストラクタ
	ModelResources();

private:
	// プレイヤー　頭モデル
	std::unique_ptr<DirectX::Model> m_playerHeadModel;
	// プレイヤー　体モデル
	std::unique_ptr<DirectX::Model> m_playerBodyModel;
	// プレイヤー　右腕モデル
	std::unique_ptr<DirectX::Model> m_playerRightArmModel;
	// プレイヤー　左腕モデル
	std::unique_ptr<DirectX::Model> m_playerLeftArmModel;
	// プレイヤー　右足モデル
	std::unique_ptr<DirectX::Model> m_playerRightFootModel;
	// プレイヤー　左足モデル
	std::unique_ptr<DirectX::Model> m_playerLeftFootModel;

	// 敵　頭モデル
	std::unique_ptr<DirectX::Model> m_enemyHeadModel;


	// 風船モデル
	std::unique_ptr<DirectX::Model> m_balloonModel;
	// 雲のモデル
	std::unique_ptr<DirectX::Model> m_cloudModel;
};