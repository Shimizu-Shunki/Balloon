#pragma once
#include "Model.h"
#include "Graphics.h"

class CommonResources;

// Resourcesクラスを定義する
class Resources
{
public:
	//	UIインプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> UI_INPUT_LAYOUT;
	//	海インプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> SEA_INPUT_LAYOUT;

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

	// スカイスフィアを取得する
	DirectX::Model* GetSkySphere() { return m_skySphere.get(); }

	// テクスチャを取得する
	// タイトルロゴを取得する
	ID3D11ShaderResourceView* GetTitleLogo() { return m_titleLogo.Get(); }
	// スタートテキストを取得する
	ID3D11ShaderResourceView* GetStartText() { return m_startText.Get(); }
	// ジャンプフレーム
	ID3D11ShaderResourceView* GetJampFrame() { return m_jampFrame.Get(); }
	// スペースキー
	ID3D11ShaderResourceView* GetSpaceKey() { return m_spaceKey.Get(); }
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
	// 海画像
	ID3D11ShaderResourceView* GetSeaTexture() { return m_SeaTexture.Get(); }


	// シェーダーを取得する
	// UI インプットレイアウトを取得する
	ID3D11InputLayout* GetUIinputLayout() { return m_UIinputLayout.Get(); }
	// UI 頂点シェーダーを取得
	ID3D11VertexShader*   GetUI_VS() { return m_UI_VS.Get(); }
	// UI ジオメトリシェーダーを取得
	ID3D11GeometryShader* GetUI_GS() { return m_UI_GS.Get(); }
	// UI ピクセルシェーダーを取得
	ID3D11PixelShader*    GetUI_PS() { return m_UI_PS.Get(); }

	// 海 インプットレイアウトを取得
	ID3D11InputLayout* GetSeaInputLayout() { return m_SeaInputLayout.Get(); }
	// 海 頂点シェーダーを取得
	ID3D11VertexShader* GetSeaVS() { return m_SeaVS.Get(); }
	// 海 ジオメトリシェーダーを取得
	ID3D11HullShader*   GetSeaHS() { return m_SeaHS.Get(); }
	// 海 ジオメトリシェーダーを取得
	ID3D11DomainShader* GetSeaDS() { return m_SeaDS.Get(); }
	// 海 ピクセルシェーダーを取得
	ID3D11PixelShader*  GetSeaPS() { return m_SeaPS.Get(); }



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
		m_enemyHeadModel{},
		m_balloonModel{},
		m_cloudModel{},
		m_spaceKey{},
		m_jampFrame{},
		m_jampMemori{},
		m_timeFrame{},
		m_timeGage{},
		m_numbers{},
		m_ruleTexture{},
		m_SeaTexture{},
		m_UIinputLayout{},
		m_UI_VS{},
		m_UI_GS{},
		m_UI_PS{},
		m_SeaInputLayout{},
		m_SeaVS{},
		m_SeaHS{},
		m_SeaDS{},
		m_SeaPS{}
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

	// 敵　頭モデル
	std::unique_ptr<DirectX::Model> m_enemyHeadModel;


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
	// スペースキー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_spaceKey;

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

	// 海画像
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SeaTexture;

	// シェーダー
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_UIinputLayout;

	// UI 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_UI_VS;
	// UI ジオメトリシェーダー
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_UI_GS;
	// UI ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_UI_PS;

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_SeaInputLayout;

	// 海 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_SeaVS;
	// 海 ハルシェーダー
	Microsoft::WRL::ComPtr<ID3D11HullShader> m_SeaHS;
	// 海 ドメインシェーダー
	Microsoft::WRL::ComPtr<ID3D11DomainShader> m_SeaDS;
	// 海 ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_SeaPS;

};