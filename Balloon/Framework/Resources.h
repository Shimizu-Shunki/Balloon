#pragma once
#ifndef RESOURCES_DEFINED
#define RESOURCES_DEFINED
#include "Model.h"
#include "Graphics.h"

// Resourcesクラスを定義する
class Resources
{
public:
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

	// 風船のモデルを取得する
	DirectX::Model* GetBalloonModel() { return m_balloonModel.get(); }
	// 雲のモデルを取得する
	DirectX::Model* GetCloudModel() { return m_cloudModel.get(); }

	// スカイスフィアを取得する
	DirectX::Model* GetSkySphere() { return m_skySphere.get(); }

public:
	Resources(Resources&&) = default;
	Resources& operator= (Resources&&) = default;
	Resources& operator= (Resources const&) = delete;
	// デストラクタ
	~Resources() = default;
	// Resoucesクラスのインスタンスを取得する
	static Resources* const GetInstance();
	// リソースをロードする
	void LoadResource();

private:
	// コンストラクタ
	Resources() noexcept
		:
		m_playerHeadModel{},
		m_playerBodyModel{},
		m_playerRightArmModel{},
		m_playerLeftArmModel{},
		m_playerRightFootModel{},
		m_playerLeftFootModel{},
		m_balloonModel{},
		m_cloudModel{}
	{
		
	}

private:
	// リソース
	static std::unique_ptr<Resources> m_resources;
	// グラフィックス
	Graphics* m_graphics = Graphics::GetInstance();
	// デバイス
	ID3D11Device* m_device = m_graphics->GetDeviceResources()->GetD3DDevice();


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

	// 風船モデル
	std::unique_ptr<DirectX::Model> m_balloonModel;
	// 雲のモデル
	std::unique_ptr<DirectX::Model> m_cloudModel;

	// スカイスフィアモデル
	std::unique_ptr<DirectX::Model> m_skySphere;
};

#endif		// RESOURCES_DEFINED