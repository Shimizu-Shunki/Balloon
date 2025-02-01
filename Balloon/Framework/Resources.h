#pragma once
#ifndef RESOURCES_DEFINED
#define RESOURCES_DEFINED
#include "Model.h"
#include "Graphics.h"

class CommonResources;

// Resourcesクラスを定義する
class Resources
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

	// 風船のモデルを取得する
	DirectX::Model* GetBalloonModel() { return m_balloonModel.get(); }
	// 雲のモデルを取得する
	DirectX::Model* GetCloudModel() { return m_cloudModel.get(); }

	// スカイスフィアを取得する
	DirectX::Model* GetSkySphere() { return m_skySphere.get(); }

	// テクスチャを取得する
	// タイトルロゴを取得する
	ID3D11ShaderResourceView* GetTitleLogo() { return m_titleLogo.Get(); }
	// スタートテキストを取得する
	ID3D11ShaderResourceView* GetStartText() { return m_startText.Get(); }
	// ジャンプフレーム
	ID3D11ShaderResourceView* GetJampFrame() { return m_jampFrame.Get(); }
	// ジャンプメモリ
	ID3D11ShaderResourceView* GetJampMemori() { return m_jampMemori.Get(); }
	// タイムフレーム
	ID3D11ShaderResourceView* GetTimeFrame() { return m_timeFrame.Get(); }
	// タイムゲージ
	ID3D11ShaderResourceView* GetTimeGage() { return m_timeGage.Get(); }
	// ナンバーズ
	ID3D11ShaderResourceView* GetNumbers() { return m_numbers.Get(); }
	// ルール画像
	ID3D11ShaderResourceView* GetRuleTexture() { return m_ruleTexture.Get(); }


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
	// 共有リソース
	CommonResources* m_commonResources;
	// デバイス
	ID3D11Device* m_device;
	// エフェクトファクトリー
	std::unique_ptr<DirectX::EffectFactory> m_effectFactory;


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

	// テクスチャ
	
	// タイトルシーン
	// タイトルロゴ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleLogo;
	// スタートテキスト
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_startText;

	// プレイシーン
	// ジャンプフレーム
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_jampFrame;
	// ジャンプメモリ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_jampMemori;
	// タイムフレーム
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_timeFrame;
	// タイムゲージ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_timeGage;
	// ナンバーズ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_numbers;

	// ルール画像
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ruleTexture;
};

#endif		// RESOURCES_DEFINED