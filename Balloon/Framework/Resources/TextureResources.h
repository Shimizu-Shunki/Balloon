#pragma once
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>

class TextureResources
{
public:
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
	// ゲームクリアテキスト
	ID3D11ShaderResourceView* GetClearTextTexture() { return m_clearText.Get(); }
	// ゲームオーバーテキスト
	ID3D11ShaderResourceView* GetFailedTextTexture() { return m_failedText.Get(); }

	// プレイヤー
	ID3D11ShaderResourceView* GetPlayerTexture() { return m_playerTexture.Get(); }
	// 敵
	ID3D11ShaderResourceView* GetEnemyTexture() { return m_enemyTexture.Get(); }

	// 肉　ノーマルマップ
	ID3D11ShaderResourceView* GetMeatNormalMap() { return m_meatNormalMap.Get(); }
	// 木　ノーマルマップ
	ID3D11ShaderResourceView* GetWoodNormalMap() { return m_woodNormalMap.Get(); }
	// 岩　ノーマルマップ
	ID3D11ShaderResourceView* GetRockNormalMap() { return m_rockNormalMap.Get(); }
	// 海　ノーマルマップ
	ID3D11ShaderResourceView* GetSeaNormalMap() { return m_seaNormalMap.Get(); }

	// キューブマップ
	ID3D11ShaderResourceView* GetCubeMap() { return m_cubeMap.Get(); }
	// キューブマップ 夕方
	ID3D11ShaderResourceView* GetEveningCubeMap() { return m_eveningCubeMap.Get(); }


public:
	TextureResources(const TextureResources&) = delete;             // コピー禁止
	TextureResources& operator=(const TextureResources&) = delete;  // コピー代入禁止
	TextureResources(const TextureResources&&) = delete;            // ムーブ禁止
	TextureResources& operator=(const TextureResources&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static TextureResources* GetInstance()
	{
		static TextureResources instance;
		return &instance;
	}
	// リソースをロードする
	void LoadResource(const nlohmann::json& data);

private:
	// コンストラクタ
	TextureResources();

private:
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

	// ゲームクリアテキスト
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_clearText;
	// ゲームクリアテキスト
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_failedText;

	// 海画像
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SeaTexture;

	// プレイヤーテクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_playerTexture;
	// 敵テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_enemyTexture;

	// 肉　ノーマルマップ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_meatNormalMap;
	// 木　ノーマルマップ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_woodNormalMap;
	// 岩　ノーマルマップ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_rockNormalMap;
	// 海　ノーマルマップ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_seaNormalMap;

	// キューブマップ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cubeMap;
	// キューブマップ　夕方
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_eveningCubeMap;
};