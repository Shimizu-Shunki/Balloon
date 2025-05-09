// ============================================
// 
// ファイル名: Resources.cpp
// 概要: 各種リソースの管理と読み込みを行うクラス（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "pch.h"
#include "Framework/Resources/Resources.h"
#include <iostream>
#include <fstream>
// 各リソース
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/ShaderResources.h"
#include "Framework/Resources/TextureResources.h"


/// <summary>
/// コンストラクタ
/// </summary>
Resources::Resources()
{
	// インスタンスを取得する
	m_modelResources    = ModelResources::GetInstance();
	m_shaderResources   = ShaderResources::GetInstance();
	m_textureResources  = TextureResources::GetInstance();
}


/// <summary>
/// 各リソースのロード
/// </summary>
void Resources::LoadResource()
{
	// JSONファイルを開く
	std::ifstream file("Resources/Json/GameResourceData.json");
	assert(file);
	// JSON をロード
	nlohmann::json data;
	file >> data; 

	// JSONファイルを開く
	std::ifstream StageDatafile("Resources/Json/StageData.json");
	assert(StageDatafile);
	// JSON をロード
	nlohmann::json StageData;
	StageDatafile >> StageData;

	// モデルをロードする
	m_modelResources->LoadResource(data);
	// シェーダーをロードする
	m_shaderResources->LoadResource(data);
	// テクスチャをロードする
	m_textureResources->LoadResource(data);
}
