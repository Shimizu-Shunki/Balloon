// ============================================
// 
// ファイル名: ShaderResources.h
// 概要: ShaderResources.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================

#pragma once
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <VertexTypes.h>


class ShaderResources
{
public:
	//	UIインプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> UI_INPUT_LAYOUT;
	//	海インプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> SEA_INPUT_LAYOUT;
public:
	// UI インプットレイアウトを取得する
	ID3D11InputLayout* GetUIinputLayout() { return m_UIinputLayout.Get(); }
	// UI 頂点シェーダーを取得
	ID3D11VertexShader* GetUI_VS()        { return m_UI_VS.Get(); }
	// UI ジオメトリシェーダーを取得
	ID3D11GeometryShader* GetUI_GS()      { return m_UI_GS.Get(); }
	// UI ピクセルシェーダーを取得
	ID3D11PixelShader* GetUI_PS()         { return m_UI_PS.Get(); }
	// UIナンバー ピクセルシェーダーを取得
	ID3D11PixelShader* GetNumberPS() { return m_numberPS.Get(); }
	// UIスコアナンバー ピクセルシェーダーを取得
	ID3D11PixelShader* GetScorePS() { return m_scorePS.Get(); }

	// 海 インプットレイアウトを取得
	ID3D11InputLayout* GetSeaInputLayout() { return m_SeaInputLayout.Get(); }
	// 海 頂点シェーダーを取得
	ID3D11VertexShader* GetSeaVS()         { return m_SeaVS.Get(); }
	// 海 ジオメトリシェーダーを取得
	ID3D11HullShader* GetSeaHS()           { return m_SeaHS.Get(); }
	// 海 ジオメトリシェーダーを取得
	ID3D11DomainShader* GetSeaDS()         { return m_SeaDS.Get(); }
	// 海 ピクセルシェーダーを取得
	ID3D11PixelShader* GetSeaPS()          { return m_SeaPS.Get(); }

	// 物理ベースレンダリング インプットレイアウトを取得
	ID3D11InputLayout* GetPBRLitInputLayout() { return m_PBRLitInputLayout.Get(); }
	// 物理ベースレンダリング 頂点シェーダーを取得
	ID3D11VertexShader* GetPBRLitVS()         { return m_PBRLitVS.Get(); }
	// 物理ベースレンダリング ピクセルシェーダーを取得
	ID3D11PixelShader* GetPBRLitPS()          { return m_PBRLitPS.Get(); }
	// 風船 ピクセルシェーダーを取得
	ID3D11PixelShader* GetBalloonPS() { return m_balloonPS.Get(); }

	// 影 頂点シェーダーを取得
	ID3D11VertexShader* GetShadowVS() { return m_ShadowVS.Get(); }
	// 影 ピクセルシェーダーを取得
	ID3D11PixelShader* GetShadowPS()  { return m_ShadowPS.Get(); }

	// スカイボックス 頂点シェーダーを取得
	ID3D11VertexShader* GetSkyBoxVS() { return m_skyBoxVS.Get(); }
	// スカイボックス ピクセルシェーダーを取得
	ID3D11PixelShader* GetSkyBoxPS()  { return m_skyBoxPS.Get(); }

public:
	ShaderResources(const ShaderResources&) = delete;             // コピー禁止
	ShaderResources& operator=(const ShaderResources&) = delete;  // コピー代入禁止
	ShaderResources(const ShaderResources&&) = delete;            // ムーブ禁止
	ShaderResources& operator=(const ShaderResources&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static ShaderResources* GetInstance()
	{
		static ShaderResources instance;
		return &instance;
	}
	// リソースをロードする
	void LoadResource(const nlohmann::json& data);

private:
	// コンストラクタ
	ShaderResources();

private:
	// UI
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_UIinputLayout;
	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader>   m_UI_VS;
	// ジオメトリシェーダー
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_UI_GS;
	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_UI_PS;

	// ナンバー　ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_numberPS;
	// ナンバー　ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_scorePS;

	// 海
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_SeaInputLayout;
	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader>   m_SeaVS;
	// ハルシェーダー
	Microsoft::WRL::ComPtr<ID3D11HullShader>     m_SeaHS;
	// ドメインシェーダー
	Microsoft::WRL::ComPtr<ID3D11DomainShader>   m_SeaDS;
	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_SeaPS;

	// 物理ベースレンダリング
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_PBRLitInputLayout;
	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader>   m_PBRLitVS;
	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_PBRLitPS;

	// 風船ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_balloonPS;

	// 影
	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader>   m_ShadowVS;
	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_ShadowPS;

	// スカイボックス
	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader>   m_skyBoxVS;
	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_skyBoxPS;

};