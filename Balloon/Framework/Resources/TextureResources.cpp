// ============================================
// 
// ファイル名: TextureResources.cpp
// 概要: テクスチャのリソースを管理するクラス（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================

#include "pch.h"
#include "Framework/Resources/TextureResources.h"
#include "Framework/CommonResources.h"
#include "Framework/Resources/Resources.h"
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>


/// <summary>
/// コンストラクタ
/// </summary>
TextureResources::TextureResources()
	:
	m_textures{}
{
	// デバイスのインスタンスを取得する
	m_device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
}


/// <summary>
/// ロードする
/// </summary>
/// <param name="data">Josnデータ</param>
void TextureResources::LoadResource(const nlohmann::json& data)
{
	// テクスチャのディレクトリを取得
	const std::wstring directory          = Resources::GetDirectoryFromJSON(data, "TextureDirectory");
	const std::wstring normalMapDirectory = Resources::GetDirectoryFromJSON(data, "NormalMapTextureDirectory");
	const std::wstring ddsDirectory       = Resources::GetDirectoryFromJSON(data, "DDSTextureDirectory");

	// テクスチャ
	if (data.contains("Textures") && data["Textures"].is_object()) 
	{
		for (const auto& [key, value] : data["Textures"].items()) 
		{
			// 無効なキーまたは非文字列値はスキップ
			if (!value.is_string() || key.empty()) continue;

			// パス構築
			std::wstring path = directory + L"/" + Resources::ConvertToWString(value);

			// テクスチャをロードする
			HRESULT hr = DirectX::CreateWICTextureFromFile(
				m_device,
				path.c_str(),
				nullptr,
				m_textures[key].ReleaseAndGetAddressOf()
			);

			// ロード失敗時はデバッグ時のみ停止
			assert(SUCCEEDED(hr)); 
		}
	}

	// ノーマルマップ
	if (data.contains("Textures_NormalMaps") && data["Textures_NormalMaps"].is_object()) 
	{
		for (const auto& [key, value] : data["Textures_NormalMaps"].items()) 
		{

			// 無効なキーまたは非文字列値はスキップ
			if (!value.is_string() || key.empty()) continue;

			// パス構築
			std::wstring path = normalMapDirectory + L"/" + Resources::ConvertToWString(value);

			// ノーマルマップをロードする
			HRESULT hr = DirectX::CreateWICTextureFromFile(
				m_device,
				path.c_str(),
				nullptr,
				m_textures[key].ReleaseAndGetAddressOf()
			);

			// ロード失敗時はデバッグ時のみ停止
			assert(SUCCEEDED(hr)); 
		}
	}

	// DDSテクスチャ
	if (data.contains("Textures_DDS") && data["Textures_DDS"].is_object()) {
		for (const auto& [key, value] : data["Textures_DDS"].items()) {

			// 無効なキーまたは非文字列値はスキップ
			if (!value.is_string() || key.empty()) continue;

			// パス構築
			std::wstring path = ddsDirectory + L"/" + Resources::ConvertToWString(value);

			// ddsテクスチャをロードする
			HRESULT hr = DirectX::CreateDDSTextureFromFile(
				m_device,
				path.c_str(),
				nullptr,
				m_textures[key].ReleaseAndGetAddressOf()
			);

			// ロード失敗時はデバッグ時のみ停止
			assert(SUCCEEDED(hr)); 
		}
	}
}

/// <summary>
/// テクスチャを取得する
/// </summary>
/// <param name="id">テクスチャID</param>
/// <returns>リソース</returns>
ID3D11ShaderResourceView* TextureResources::GetTexture(TextureKeyID id)
{
	// キーをstring型に変更
	std::string key = std::string(magic_enum::enum_name(id));

	// 検索
	auto it = m_textures.find(key);
	return (it != m_textures.end()) ? it->second.Get() : nullptr;
}