#pragma once
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

class CommonResources;

class ModelResources;
class ShaderResources;
class TextureResources;
class MaterialResources;

// Resourcesクラスを定義する
class Resources
{
public:
	// 簡易的な UTF-8 → UTF-16 変換
	static std::wstring ConvertToWString(const std::string& str) {
		return std::wstring(str.begin(), str.end()); 
	};

public:
	// モデルリソースを取得する
	ModelResources* GetModelResources() { return m_modelResources; }
	// シェーダーリソースを取得する
	ShaderResources* GetShaderResources() { return m_shaderResources; }
	// テクスチャリソースを取得する
	TextureResources* GetTextureResources() { return m_textureResources; }
	// マテリアルリソースを取得する
	MaterialResources* GetMaterialResources() { return m_materialResources; }

public:
	Resources(const Resources&) = delete;             // コピー禁止
	Resources& operator=(const Resources&) = delete;  // コピー代入禁止
	Resources(const Resources&&) = delete;            // ムーブ禁止
	Resources& operator=(const Resources&&) = delete; // ムーブ代入禁止

	//	シングルトンインスタンスの取得
	static Resources* GetInstance()
	{
		static Resources instance;
		return &instance;
	}
	// リソースをロードする
	void LoadResource();

private:
	// コンストラクタ
	Resources();
	
private:
	// モデルリソース
	ModelResources* m_modelResources;
	// シェーダーリソース
	ShaderResources* m_shaderResources;
	// テクスチャリソース
	TextureResources* m_textureResources;
	// マテリアルリソース
	MaterialResources* m_materialResources;
};